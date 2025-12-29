/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:28:09 by wshee             #+#    #+#             */
/*   Updated: 2025/12/29 23:56:37 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

bool check_map_character(char c);
void print_2d_map(char **array);
void allocate_map_array(t_map *map);
bool validate_player(t_map *map, t_player *player);
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
// total rows = map_rows + top + bottom + NULL
// when allocate for map_map_column +2, as i = 0,
// for each row, 2 for space and 1 for '\0'
void allocate_map_array(t_map *map)
{
	// printf("rows: %d, map_map_column: %d\n", map->map_rows, map->map_column);
	map->map_arr = (char **)malloc(sizeof(char*) * (map->map_rows + 3));
	if(!map->map_arr)
	{
		ft_putstr_fd("Failed to malloc\n", 2);
		return ;
	}
	int i = 0;
	while (i < map->map_rows + 2)
	{
		map->map_arr[i] = (char *)malloc(sizeof(char) * (map->map_column + 3));
		if(!map->map_arr[i])
		{
			ft_putstr_fd("Failed to malloc\n", 2);
			return ;
		}
		ft_memset(map->map_arr[i], ' ', map->map_column + 2);
		map->map_arr[i][map->map_column + 2] = '\0';
		i++;
	}
	map->map_arr[i] = NULL;
	// print_2d_map(map->map_arr);
}

/**
 * read file in map section and store the map in a 2d array
 */
void store_2d_array(t_map *map, const char *filename)
{
	int fd;
	t_parse_state type;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", fd);
		ft_putendl_fd("Invalid fd: Failed to open file", 2);
		return ;
	}
	char *line = get_next_line(fd);
	int row = 1;
	while (line)
	{
		type = identify_parse_state(line[0]);
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
			map->map_arr[row][col++] = line[i++];
		}
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
	// print_2d_map(map->map_arr);
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
 * calculate the row and map_column of map
 * if see newline in section map, return error
 * store the maximum length for map_column
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
			printf("Invalid character in map: [%c] at row %d map_column %d\n", line[i], map->map_rows, i);
			return false;
		}
		i++;
	}
	if (map->map_column < len)
		map->map_column = len;
	map->map_rows++;
	return true;
}

bool validate_player(t_map *map, t_player *player)
{
	int i = 0;
	int player_count = 0;
	while (map->map_arr[i])
	{
		int j = 0;
		while (map->map_arr[i][j] != '\0')
		{
			if (map->map_arr[i][j] == 'N' || map->map_arr[i][j] == 'S' || map->map_arr[i][j] == 'E' || map->map_arr[i][j] == 'W')
			{
				player->direction = map->map_arr[i][j];
				player->pos_x = (double)j;
				player->pos_y = (double)i;
				player_count++;
			}
			j++;
		}
		i++;
	}
	// printf("player: %d pos >> x: %d, y: %d\n", player, data->player.pos_x, data->player.pos_y);
	if (player_count == 1)
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
bool validate_map(t_map *map, t_player *player)
{
	int i = 0;
	while (map->map_arr[i])
	{
		int j = 0;
		while (map->map_arr[i][j] != '\0')
		{
			if (map->map_arr[i][j] == '0' || ((double)j == player->pos_x && (double)i == player->pos_y))
			{
				// printf("check no walls >> [%c] x: %d, y: %d\n", map->map_arr[i][j], j, i);
				if (!check_walls(map->map_arr[i - 1][j]) || !check_walls(map->map_arr[i + 1][j]) || !check_walls(map->map_arr[i][j - 1]) || !check_walls(map->map_arr[i][j + 1]))
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
	if (!validate_player(&data->map, &data->player))
	{
		return(error_message("Map should consists of one player only"));
	}
	if (!validate_map(&data->map, &data->player))
	{
		return (error_message("Invalid map: Map not close with walls"));
	}
	return 1;
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
