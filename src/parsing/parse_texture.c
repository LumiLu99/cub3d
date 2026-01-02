/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:42:28 by wshee             #+#    #+#             */
/*   Updated: 2026/01/02 13:33:24 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	handle_walls(char *identifier, char *path, t_data *data);
static int	handle_floor_n_ceiling(char *element, char *path, t_data *data);
static int	validate_texture(char **texture);
int			parse_texture(char *line, t_data *data);

static int	handle_walls(char *identifier, char *path, t_data *data)
{
	int			i;
	int			fd;
	const char	*texture[4] = {"NO", "EA", "SO", "WE"};

	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(identifier, texture[i], ft_strlen(identifier)) == 0)
		{
			if (data->tex[i].tex_path != NULL)
				return (error_message("Duplicate elements found: texture"));
			data->tex[i].tex_path = ft_strdup(path);
			if (!check_open_file(path, ".xpm", &fd, INVALID_XPM_FILE_EXT))
				return (0);
			close(fd);
		}
		i++;
	}
	return (1);
}

static int	handle_floor_n_ceiling(char *element, char *path, t_data *data)
{
	int	color;

	if (ft_strlen(element) == 1 && (element[0] == 'F' || element[0] == 'C'))
	{
		if (element[0] == 'F' && data->map.floor != -1)
			return (error_message("Duplicate elements found: floor"));
		if (element[0] == 'C' && data->map.ceiling != -1)
			return (error_message("Duplicate elements found: ceiling"));
		color = parse_color(element, path);
		if (color == -1)
			return (error_message("Invalid RGB color"));
		if (element[0] == 'F')
			data->map.floor = color;
		else
			data->map.ceiling = color;
	}
	return (1);
}

static int	validate_texture(char **texture)
{
	int	counter;

	counter = 0;
	if (!texture)
		return (error_message("Failed to split texture"));
	while (texture[counter])
		counter++;
	if (counter != 2)
		return (error_message("Invalid element format"));
	if (ft_strlen(texture[0]) > 2)
		return (error_message("Invalid type identifier"));
	return (1);
}

// for tecture path, use strdup to allocate new memory to store the value,
// avoid dangling pointer when point to split array
int	parse_texture(char *line, t_data *data)
{
	char	**texture;
	char	*texture_path;
	int		result;

	texture_path = NULL;
	texture = ft_split(line, ' ');
	if (!validate_texture(texture))
	{
		cleanup_texture(texture, texture_path);
		return (0);
	}
	texture_path = ft_strtrim(texture[1], "\t\n");
	if (!texture_path)
	{
		cleanup_texture(texture, texture_path);
		return (error_message("Failed to strtrim string"));
	}
	result = 1;
	if (!handle_walls(texture[0], texture_path, data))
		result = 0;
	if (!handle_floor_n_ceiling(texture[0], texture_path, data))
		result = 0;
	cleanup_texture(texture, texture_path);
	return (result);
}
