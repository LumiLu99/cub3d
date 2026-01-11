/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:28:09 by wshee             #+#    #+#             */
/*   Updated: 2026/01/11 18:13:56 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	create_map(int *row, t_map *map, char *line);
static void	store_2d_array(t_map *map, const char *filename);
static void	allocate_map_array(t_map *map);
int			parse_map(const char *filename, t_data *data);
bool		player_direction(char c);

static void	create_map(int *row, t_map *map, char *line)
{
	int	i;
	int	col;

	i = 0;
	col = 1;
	while (line[i] != '\n' && line[i] != '\0')
	{
		map->map_arr[*row][col++] = line[i++];
	}
	(*row)++;
}

/**
 * read file in map section and store the map in a 2d array
 */
static void	store_2d_array(t_map *map, const char *filename)
{
	int		fd;
	int		row;
	char	*line;
	t_state	type;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Invalid fd: Failed to open file", 2);
		return ;
	}
	line = get_next_line(fd);
	row = 1;
	while (line)
	{
		type = identify_state(line[0]);
		if (type == MAP)
			create_map(&row, map, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

// add outder border around the map
// total rows = map_rows + top + bottom + NULL
// when allocate for map_map_column +2, as i = 0,
// for each row, 2 for space and 1 for '\0'
static void	allocate_map_array(t_map *map)
{
	int	i;

	map->map_arr = (char **)malloc (sizeof(char *) * (map->map_rows + 3));
	if (!map->map_arr)
	{
		ft_putstr_fd("Failed to malloc\n", 2);
		return ;
	}
	i = 0;
	while (i < map->map_rows + 2)
	{
		map->map_arr[i] = (char *)malloc (sizeof(char) * (map->map_column + 3));
		if (!map->map_arr[i])
		{
			ft_putstr_fd("Failed to malloc\n", 2);
			return ;
		}
		ft_memset(map->map_arr[i], ' ', map->map_column + 2);
		map->map_arr[i][map->map_column + 2] = '\0';
		i++;
	}
	map->map_arr[i] = NULL;
}

int	parse_map(const char *filename, t_data *data)
{
	allocate_map_array(&data->map);
	store_2d_array(&data->map, filename);
	if (!validate_player(data->map.map_arr, &data->player))
		return (error_message("Map should consists of one player only"));
	if (!validate_map(&data->map, &data->player))
		return (error_message("Invalid map: Map not close with walls"));
	return (1);
}

bool	player_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
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
