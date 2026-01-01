# include "../../includes/cub3d.h"

static bool check_map_character(char c);
bool read_map(t_map *map, char *line);
static bool check_walls(char c);
bool validate_map(t_map *map, t_player *player);
bool validate_player(t_map *map, t_player *player);

static bool check_map_character(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != ' ')
		return false;
	return true;
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

static bool check_walls(char c)
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
