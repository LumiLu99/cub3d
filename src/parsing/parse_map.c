/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:28:09 by wshee             #+#    #+#             */
/*   Updated: 2025/12/28 14:52:23 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

bool check_map_character(char c);
void print_2d_map(char **array);
void allocate_map_array(t_map *map);
bool validate_player(t_map *map);
void store_2d_array(t_map *map, const char *filename);
bool read_map(t_map *map, char *line);
int parse_map(const char *filename, t_data *data);

bool check_map_character(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != ' ')
		return false;
	return true;
}

// add outder border around the map
// total rows = sum_rows + top + bottom + NULL
// when allocate for column +2, as i = 0,
// for each row, 2 for space and 1 for '\0'
void allocate_map_array(t_map *map)
{
	// printf("rows: %d, column: %d\n", map->sum_rows, map->column);
	map->array = (char **)malloc(sizeof(char*) * (map->sum_rows + 3));
	if(!map->array)
	{
		ft_putstr_fd("Failed to malloc\n", 2);
		return ;
	}
	int i = 0;
	while (i < map->sum_rows + 2)
	{
		map->array[i] = (char *)malloc(sizeof(char) * (map->column + 3));
		if(!map->array[i])
		{
			ft_putstr_fd("Failed to malloc\n", 2);
			return ;
		}
		ft_memset(map->array[i], ' ', map->column + 2);
		map->array[i][map->column + 2] = '\0';
		i++;
	}
	map->array[i] = NULL;
	// print_2d_map(map->array);
}

/**
 * read file in map section and store the map in a 2d array
 */
void store_2d_array(t_map *map, const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Invalid fd: Failed to open file\n");
		return ;
	}
	char *line = get_next_line(fd);
	int row = 1;
	while (line)
	{
		t_parse_state type = identify_parse_state(line);
		if (line[0] == '\n' || type == ELEMENTS)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		int i = 0;
		int col = 1;
		while (line[i] != '\n')
		{
			map->array[row][col++] = line[i++];
		}
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
	// print_2d_map(map->array);
}

void print_2d_map(char **array)
{
	for (int i = 0; array[i] != NULL; i++)
	{
		printf("array[%d]: [", i);
		for (int j = 0; array[i][j] != '\0'; j++)
			printf("%c", array[i][j]);
		printf("]\n");
	}
}

/**
 * calculate the row and column of map
 * if see newline in section map, return error
 * store the maximum length for column
 */
bool read_map(t_map *map, char *line)
{
	int len;
	int i;

	if (line[0] == '\n')
	{
		return (error_message("Empty lines in the map"));
	}
	len = ft_strlen(line) - 1;
	i = 0;
	while (i < len - 1)
	{
		if (!check_map_character(line[i]))
		{
			printf("Invalid character in map: [%c] at row %d column %d\n", line[i], map->sum_rows, i);
			return false;
		}
		i++;
	}
	if (map->column < len)
		map->column = len;
	map->sum_rows++;
	return true;
}

bool validate_player(t_map *map)
{
	int i = 0;
	int player = 0;
	while (map->array[i])
	{
		int j = 0;
		while (map->array[i][j] != '\0')
		{
			if (map->array[i][j] == 'N' || map->array[i][j] == 'S' || map->array[i][j] == 'E' || map->array[i][j] == 'W')
			{
				map->x_pos = j;
				map->y_pos = i;
				player++;
			}
			j++;
		}
		i++;
	}
	// printf("player: %d pos >> x: %d, y: %d\n", player, map->x_pos, map->y_pos);
	if (player == 1)
		return true;
	return false;
}

bool check_walls(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return false;
	return true;
}

// when see 0 or player check four direction is fill with walls
bool validate_map(t_map *map)
{
	int i = 0;
	while (map->array[i])
	{
		int j = 0;
		while (map->array[i][j] != '\0')
		{
			if (map->array[i][j] == '0' || (j == map->x_pos && i == map->y_pos))
			{
				// printf("check no walls >> [%c] x: %d, y: %d\n", map->array[i][j], j, i);
				if (!check_walls(map->array[i - 1][j]) || !check_walls(map->array[i + 1][j]) || !check_walls(map->array[i][j - 1]) || !check_walls(map->array[i][j + 1]))
				{
					// printf("no walls >> x: %d, y: %d\n", j, i);
					return false;
				}
			}
			j++;
		}
		i++;
	}
	return true;
}

int parse_map(const char *filename, t_data *data)
{
	allocate_map_array(&data->map);
	store_2d_array(&data->map, filename);
	if (!validate_player(&data->map))
	{
		return(error_message("Map should consists of one player only"));
	}
	if (!validate_map(&data->map))
	{
		return (error_message("Invalid map: Map not close with walls"));
	}
	return 1;
}

void init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->map.floor = -1;
	data->map.ceiling = -1;
}

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
	{
		ft_putstr_fd("Number of arguments must be 2", 2);
		return 1;
	}
	init_data(&data);
	if (!parse_file(av[1], &data))
	{
		cleanup_data(&data);
		return 1;
	}
	if (!parse_map(av[1], &data))
	{
		cleanup_data(&data);
		return 1;
	}
	return 0;
}

// Requirements:
// 1. map must composed of 0 & 1 & (N/S/E/W)
// -use get next line
// -read the map and store in 2D array
// 2. map must be surrounded by walls
// first and last row must be 1 and space
// else start and end with 1
// else return error
// 3. elements: textures(NO/SO/WE/EA), floor color, ceiling color
// - check file extension of texture file, end with .xpm
// - check the colour must between 0-255 for each RGB
// - convert to hexa format
// - map must be last, others can be any order
// 4. check player up, down, left, right
// - is 1 or 0
// - make a 2d array, fill up the corner with space

// Edge cases!
// check get next line make sure read until the end
// will have meory leaks if didnt read the end
// check tabs for texture after split
// what if the texture is not 6 (missing)
