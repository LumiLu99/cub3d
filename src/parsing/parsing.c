/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:28:09 by wshee             #+#    #+#             */
/*   Updated: 2025/11/29 22:59:36 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"
# include <stdio.h>

bool check_file_ext(const char *filename)
{
	const char *ext = ".cub";
	size_t filename_len = ft_strlen(filename);
	size_t ext_len = ft_strlen(ext);

	if (filename[0] == '\0')
		return false;
	if (filename_len == ext_len)
		return false;
	while (filename[filename_len - 1] && ext_len > 0)
	{
		if (filename[filename_len - 1] != ext[ext_len - 1])
			return false;
		filename_len--;
		ext_len--;
	}
	return true;
}

// bool validate_walls(char *line, int check_walls)
// {
// 	int	i;
// 	int len;

// 	check_walls = 0;
// 	// exclude the '\n'
// 	len = ft_strlen(line) - 2;
// 	while (i < len)
// 	{
// 		if (check_walls = 1)
// 		{
// 			if (line[i] != '1' && line[i] != ' ')
// 				return false;
// 		}
// 		else
// 		{
// 			if (line[i] == '1' && line [i + 1] != 0)
// 				return false;
// 		}
// 		i++;
// 	}
// }

bool check_character(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != ' ' && c != '\n')
		return false;
	return true;
}

void allocate_map_array(t_map *map)
{
	char **array = (char **)malloc(sizeof(char*) * map->sum_rows);
	if(!array)
	{
		ft_putstr_fd("Failed to malloc\n", 2);
	}
	int i = 0;
	while(i < map->sum_rows)
	{
		array[i] = (char *)malloc(sizeof(char) * map->column);
		i++;
	}
}

// calculate the row of map
void read_map(t_map *map, int fd)
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
		return ;
	}
	while (line)
	{
		if (line[0] == '\n')
		{
			printf("Empty lines in the map\n");
			return ;
		}
		int i = 0;
		while (line[i])
		{
			if (!check_character(line[i]))
			{
				printf("Invalid character\n");
				return ;
			}
			i++;
		}
		int len = ft_strlen(line) - 1;
		if (column < len)
			column = len;
		// if (rows == 0)
		// 	check_walls = 1;
		// if(!validate_walls(line, check_walls))
		// {
		// 	printf("Invalid map\n");
		// 	return ;
		// }
		rows++;
		free(line);
		line = get_next_line(fd);
	}
	map->sum_rows = rows;
	map->column = column;
	printf("row: %d, column: %d\n", map->sum_rows, map->column);
}

int parse_map(const char *filename, t_map *map)
{
	int	fd;

	if (!check_file_ext(filename))
	{
		printf("Invalid map\n");
		return 1;
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open file\n");
		return 1;
	}
	ft_bzero(map, sizeof(t_map));
	read_map(map, fd);
	allocate_map_array(map);
	return 0;
}

int	main(int ac, char **av)
{
	t_map map;
	if (ac != 2)
	{
		printf("Number of arguments must be 2\n");
		return 1;
	}
	if (parse_map(av[1], &map))
		return 1;
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
// 4. check player up, down, left, right
// - is 1 or 0
// - make a 2d array, fill up the corner with space
