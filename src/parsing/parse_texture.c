/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:42:28 by wshee             #+#    #+#             */
/*   Updated: 2025/12/28 20:10:23 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

// for tecture path, use strdup to allocate new memory to store the value,
// avoid dangling pointer when point to split array
int parse_texture(char *line, t_data *data)
{
	char **texture;
	int counter;
	char *identifier;
	char *texture_path;
	int i;
	const char *texture_identifier[4] = {"NO", "EA", "SO", "WE"};

	texture_path = NULL;
	texture = ft_split(line, ' ');
	if (!texture)
		return (error_message("Failed to split texture"));
	counter = 0;
	while (texture[counter])
		counter++;
	if (counter != 2)
	{
		cleanup_texture(texture, texture_path);
		return (error_message("Invalid element format"));
	}
	identifier = texture[0];
	if (ft_strlen(identifier) > 2)
	{
		cleanup_texture(texture, texture_path);
		return (error_message("Invalid type identifier"));
	}
	texture_path = ft_strtrim(texture[1], "\t\n");
	if (!texture_path)
	{
		cleanup_texture(texture, texture_path);
		return (error_message("Failed to strtrim string"));
	}
	i = 0;
	while(i < 4)
	{
		if (ft_strncmp(identifier, texture_identifier[i], ft_strlen(identifier)) == 0)
		{
			if (data->tex[i].tex_path != NULL)
			{
				cleanup_texture(texture, texture_path);
				return(error_message("Duplicate elements found: texture"));
			}
			data->tex[i].tex_path = ft_strdup(texture_path);
			if (!check_file_ext(texture_path, ".xpm"))
			{
				cleanup_texture(texture, texture_path);
				return (error_message("Invalid texture file: must be end with .xpm"));
			}
			int fd = open(texture_path, O_RDONLY);
			if (fd == -1)
			{
				cleanup_texture(texture, texture_path);
				return (error_message("Invalid fd: Failed to open .xpm file"));
			}
			close(fd);
		}
		i++;
	}
	if (ft_strlen(identifier) == 1 && (line[0] == 'F' || line[0] == 'C'))
	{
		if (data->map.floor == -1 || data->map.ceiling == -1)
		{
			int color = parse_color(identifier, texture_path);
			if (color == -1)
			{
				cleanup_texture(texture, texture_path);
				return (error_message("Invalid RGB color"));
			}
			if (line[0] == 'F')
				data->map.floor = color;
			else
				data->map.ceiling = color;
		}
		else
		{
			cleanup_texture(texture, texture_path);
			return (error_message("Duplicate elements found: floor and ceiling"));
		}
	}
	cleanup_texture(texture, texture_path);
	return 1;
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

int identify_parse_state(char *line)
{
	if (line[0] == 'N' || line[0] == 'W' || line[0] == 'S' || line[0] == 'E' || line[0] == 'F' || line[0] == 'C')
		return ELEMENTS;
	else if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
		return MAP;
	else
		return INVALID;
}

/**
 * this function verifies the sequence of the elements in the map file
 * divided into 2 section: ELEMENTS and MAP (in order)
 * must start with section ELEMENTS (can be seperated by new line)
 * skip when see new line or error
 * let it read until the end of the file
 * store error flag when there is error, after finish read only exit
 * identify the type of each line
 * when reach map, check each element has their own value
 * when found element in map, return error
 * at the end validate the last part is map
 */
int parse_file(const char *filename, t_data *data)
{
	t_parse_state	state;
	int				error;
	int				fd;
	char			*line;

	state = ELEMENTS;
	error = 0;
	if (!check_file_ext(filename, ".cub"))
		return (error_message("Invalid map: map file extension must be \".cub\"\n"));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (error_message("Invalid fd: Failed to open file"));
	line = get_next_line(fd);
	while (line)
	{
		if ((line[0] == '\n' && state == ELEMENTS) || error == -1)
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		t_parse_state type = identify_parse_state(line);
		if (state == ELEMENTS)
		{
			if (type == MAP)
			{
				if(!check_all_element_exists(data))
				{
					error = -1;
					free(line);
					line = get_next_line(fd);
					continue ;
				}
				state = MAP;
			}
			else if (!parse_texture(line, data))
			{
				error = -1;
				free(line);
				line = get_next_line(fd);
				continue ;
			}
		}
		if (state == MAP)
		{
			if (!read_map(&data->map, line))
			{
				error = -1;
				free(line);
				line = get_next_line(fd);
				continue ;
			}
		}
		if (type == INVALID)
		{
			ft_putendl_fd("Error", 2);
			ft_putendl_fd("Invalid element in file", 2);
			error = -1;
			free(line);
			line = get_next_line(fd);
			continue ;

		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (error == -1)
		return 0;
	if (state == ELEMENTS)
		return (error_message("No textures or map found"));
	return 1;
}
