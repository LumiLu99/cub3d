/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:02:24 by wshee             #+#    #+#             */
/*   Updated: 2026/01/02 13:24:31 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	check_map_character(char c);
bool		read_map(t_map *map, char *line);
static bool	check_walls(char c);
bool		validate_map(t_map *map, t_player *player);
bool		validate_player(char **map, t_player *player);

static bool	check_map_character(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W'
		&& c != 'E' && c != ' ')
		return (false);
	return (true);
}

/**
 * calculate the row and map_column of map
 * if see newline in section map, return error
 * store the maximum length for map_column
 */
bool	read_map(t_map *map, char *line)
{
	int	len;
	int	i;

	if (line[0] == '\n')
	{
		return (error_message("Empty lines in the map"));
	}
	len = ft_strlen(line) - 1;
	i = 0;
	while (i < len - 1)
	{
		if (!check_map_character(line[i]))
			return (error_message("Invalid character in map"));
		i++;
	}
	if (map->map_column < len)
		map->map_column = len;
	map->map_rows++;
	return (true);
}

static bool	check_walls(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (false);
	return (true);
}

// when see 0 or player check four direction is fill with walls
bool	validate_map(t_map *map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (map->map_arr[i])
	{
		j = 0;
		while (map->map_arr[i][j] != '\0')
		{
			if (map->map_arr[i][j] == '0'
				|| ((double)j == player->pos_x && (double)i == player->pos_y))
			{
				if (!check_walls(map->map_arr[i - 1][j])
					|| !check_walls(map->map_arr[i + 1][j])
					|| !check_walls(map->map_arr[i][j - 1])
					|| !check_walls(map->map_arr[i][j + 1]))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_player(char **map, t_player *player)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (player_direction(map[i][j]))
			{
				player->direction = map[i][j];
				player->pos_x = (double)j;
				player->pos_y = (double)i;
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count == 1)
		return (true);
	return (false);
}
