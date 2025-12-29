/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:42:28 by wshee             #+#    #+#             */
/*   Updated: 2025/12/29 23:54:06 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

static int handle_walls(char *identifier, char *texture_path, t_data *data);
static int handle_floor_and_ceiling(char *identifier, char *texture_path, t_data *data);
static int validate_texture(char **texture);

static int handle_walls(char *identifier, char *texture_path, t_data *data)
{
	int i;
	int fd;
	const char *texture_identifier[4] = {"NO", "EA", "SO", "WE"};

	i = 0;
	while(i < 4)
	{
		if (ft_strncmp(identifier, texture_identifier[i], ft_strlen(identifier)) == 0)
		{
			if (data->tex[i].tex_path != NULL)
				return(error_message("Duplicate elements found: texture"));
			data->tex[i].tex_path = ft_strdup(texture_path);
			if (!check_and_open_file(texture_path, ".xpm", &fd, INVALID_XPM_FILE_EXT))
				return 0;
			close(fd);
		}
		i++;
	}
	return 1;
}

static int handle_floor_and_ceiling(char *identifier, char *texture_path, t_data *data)
{
	int color;

	if (ft_strlen(identifier) == 1 && (identifier[0] == 'F' || identifier[0] == 'C'))
	{
		if (identifier[0] == 'F' && data->map.floor != -1 )
			return (error_message("Duplicate elements found: floor"));
		if (identifier[0] == 'C' && data->map.ceiling != -1)
			return (error_message("Duplicate elements found: ceiling"));
		color = parse_color(identifier, texture_path);
		if (color == -1)
			return (error_message("Invalid RGB color"));
		if (identifier[0] == 'F')
			data->map.floor = color;
		else
			data->map.ceiling = color;
	}
	return 1;
}

static int validate_texture(char **texture)
{
	int counter;

	counter = 0;
	if (!texture)
		return (error_message("Failed to split texture"));
	while (texture[counter])
		counter++;
	if (counter != 2)
		return (error_message("Invalid element format"));
	if (ft_strlen(texture[0]) > 2)
		return (error_message("Invalid type identifier"));
	return 1;
}

// for tecture path, use strdup to allocate new memory to store the value,
// avoid dangling pointer when point to split array
int parse_texture(char *line, t_data *data)
{
	char **texture;
	char *texture_path;
	int result;

	texture_path = NULL;
	texture = ft_split(line, ' ');
	if (!validate_texture(texture))
	{
		cleanup_texture(texture, texture_path);
		return 0;
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
	if (!handle_floor_and_ceiling(texture[0], texture_path, data))
		result = 0;
	cleanup_texture(texture, texture_path);
	return (result);
}

bool check_all_element_exists(t_data *data)
{
	int i = 0;
	while (i < 4)
	{
		if (data->tex[i].tex_path == NULL)
			return(error_message("Texture elements given incomplete"));
		i++;
	}
	if (data->map.floor == -1 || data->map.ceiling == -1)
		return(error_message("Floor and ceiling elements given incomplete"));
	return true;
}

int identify_parse_state(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E' || c == 'F' || c == 'C')
		return ELEMENTS;
	else if (c == ' ' || c == '1' || c == '0')
		return MAP;
	return INVALID;
}

bool check_and_open_file(const char *file, const char *ext, int *fd, char *msg)
{
	if (!check_file_ext(file, ext))
		return (error_message(msg));
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		return (error_message("Invalid fd or path: Failed to open file"));
	return true;
}
