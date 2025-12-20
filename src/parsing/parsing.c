/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:28:09 by wshee             #+#    #+#             */
/*   Updated: 2025/12/20 22:30:27 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

bool check_file_ext(const char *filename, const char *ext);
bool check_character(char c);
int open_file(const char *filename);
void print_2d_map(char **array);
void allocate_map_array(t_map *map);
bool validate_player(t_map *map);
void store_2d_array(t_map *map, const char *filename);
bool read_map(t_map *map, int fd);
int parse_map(const char *filename, t_map *map);

bool check_file_ext(const char *filename, const char *ext)
{
	size_t filename_len = ft_strlen(filename);
	size_t ext_len = ft_strlen(ext);

	if (filename[0] == '\0')
		return false;
	if (filename_len <= ext_len)
		return false;
	while (filename[filename_len - 1] && ext_len > 0)
	{
		// printf("filename[%c], ext[%c]\n", filename[filename_len - 1], ext[ext_len - 1]);
		if (filename[filename_len - 1] != ext[ext_len - 1])
			return false;
		// printf("filename_len: %zu, ext: %zu\n", filename_len, ext_len);
		filename_len--;
		ext_len--;
	}
	return true;
}

bool check_character(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != ' ')
		return false;
	return true;
}

void allocate_map_array(t_map *map)
{
	map->array = (char **)malloc(sizeof(char*) * (map->sum_rows + 3));
	if(!map->array)
	{
		ft_putstr_fd("Failed to malloc\n", 2);
		return ;
	}
	int i = 0;
	while (i < map->sum_rows + 3)
	{
		// 2 for space and 1 for '\0'
		map->array[i] = (char *)malloc(sizeof(char) * (map->column + 3));
		if(!map->array[i])
		{
			ft_putstr_fd("Failed to malloc\n", 2);
			return ;
		}
		i++;
	}
}

void store_2d_array(t_map *map, const char *filename)
{
	int fd = open_file(filename);
	char *line = get_next_line(fd);
	int row = 0;
	// Set the top border
	ft_memset(map->array[row], ' ', map->column + 2);
	map->array[row++][map->column + 2] = '\0';
	while (row < map->sum_rows + 1)
	{
		ft_memset(map->array[row], ' ', map->column + 2);
		int i = 0;
		int col = 1;
		while (line[i] != '\n')
		{
			map->array[row][col++] = line[i++];
		}
		map->array[row][map->column + 2] = '\0';
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
	// Set the bottom border
	ft_memset(map->array[row], ' ', map->column + 2);
	map->array[row++][map->column + 2] = '\0';
	map->array[row] = NULL;
	print_2d_map(map->array);
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

// calculate the row of map
bool read_map(t_map *map, int fd)
{
	int	rows;
	int	check_walls;
	int	column;
	char	*line;

	rows = 0;
	check_walls = 0;
	column = 0;
	line = get_next_line(fd);
	if (!line)
	{
		printf("Error: Empty map! \n");
		return false;
	}
	while (line)
	{
		if (line[0] == '\n')
		{
			printf("Empty lines in the map\n");
			return false;
		}
		int i = 0;
		// exclude '\n'
		int len = ft_strlen(line) - 1;
		while (i < len - 1)
		{
			if (!check_character(line[i]))
			{
				printf("Invalid character: [%c] at row %d column %d\n", line[i], rows, i);
				return false;
			}
			i++;
		}
		if (column < len)
			column = len;
		rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->sum_rows = rows;
	map->column = column;
	printf("row: %d, column: %d\n", map->sum_rows, map->column);
	return true;
}

int open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open file\n");
		return (-1);
	}
	return fd;
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
	printf("player: %d pos >> x: %d, y: %d\n", player, map->x_pos, map->y_pos);
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

int parse_map(const char *filename, t_map *map)
{
	int fd = open_file(filename);
	ft_bzero(map, sizeof(t_map));
	if(!read_map(map, fd))
	{
		return 1;
	}
	allocate_map_array(map);
	store_2d_array(map, filename);
	if (!validate_player(map))
	{
		ft_putstr_fd("Map should consists of one player only", 2);
		return 1;
	}
	if (!validate_map(map))
	{
		ft_putstr_fd("Invalid map: Map not close with walls", 2);
		return 1;
	}
	return 0;
}

void init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->map.floor = -1;
	data->map.ceiling = -1;
}

int	main(int ac, char **av)
{
	// t_map map;
	// t_img tex[4];
	t_data data;

	if (ac != 2)
	{
		printf("Number of arguments must be 2\n");
		return 1;
	}
	// TODO: how to separate and differentiate textures and map? think think... ft_split '\n'
	init_data(&data);
	if (parse_file(av[1], &data))
		return 1;
	// if (parse_map(av[1], &map))
	// 	return 1;
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
