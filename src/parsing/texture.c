/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:42:28 by wshee             #+#    #+#             */
/*   Updated: 2025/12/21 19:25:53 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

bool error_message(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	return false;
}

int parse_color(char *identifier, char *color)
{
	char **rgb = ft_split(color, ',');
	int counter = 0;
	while (rgb[counter])
		counter++;
	if (counter != 3)
		return (-1);
	int r = convert_rgb_to_int(rgb[0]);
	int g = convert_rgb_to_int(rgb[1]);
	int b = convert_rgb_to_int(rgb[2]);
	// convert into hexa format 0xFFFFFF in integer form
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}

int parse_texture(char *line, t_data *data)
{
	const char *texture_identifier[4] = {"NO", "EA", "SO", "WE"};
	char **texture = ft_split(line, ' ');
	if (!texture)
	{
		return (error_message("Failed to split texture"));
	}
	int counter = 0;
	while (texture[counter])
		counter++;
	if (counter != 2)
		return (error_message("Invalid element format"));
	char *identifier = texture[0];
	// printf("counter: %d, identifier: %s\n", counter, identifier);
	if (ft_strlen(identifier) > 2)
	{
		return (error_message("Invalid type identifier"));
	}
	char *texture_path = ft_strtrim(texture[1], "\t\n");
	if (!texture_path)
		return (error_message("Failed to strtrim string"));
	// printf("texture path: %s\n", texture_path);
	int i = 0;
	while(i < 4)
	{
		if (ft_strncmp(identifier, texture_identifier[i], ft_strlen(identifier)) == 0)
		{
			if (data->tex[i].tex_path != NULL)
				return(error_message("Duplicate elements found: texture"));
			data->tex[i].tex_path = ft_strdup(texture_path);
			// printf("tex: %s\n", data->tex[i].tex_path);
			if (!check_file_ext(texture_path, ".xpm"))
				return (error_message("Invalid texture file: must be end with .xpm"));
		}
		i++;
	}
	if (ft_strlen(identifier) == 1 && (line[0] == 'F' || line[0] == 'C'))
	{
		if (data->map.floor == -1 || data->map.ceiling == -1)
		{
			int color = parse_color(identifier, texture_path);
			if (color == -1)
				return (error_message("Invalid RGB color"));
			// printf("color: %d\n", color);
			if (line[0] == 'F')
				data->map.floor = color;
			else
				data->map.ceiling = color;
		}
		else
			return (error_message("Duplicate elements found: floor and ceiling"));
	}
	// TODO: free everything, write function free 2d array
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

int parse_file(const char *filename, t_data *data)
{
	t_parse_state	state;
	int error;

	state = ELEMENTS;
	error = 0;
	if (!check_file_ext(filename, ".cub"))
	{
		return (error_message("Invalid map: map file extension must be \".cub\"\n"));
	}
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (error_message("Invalid fd: Failed to open file"));
	char *line = get_next_line(fd);
	while (line)
	{
		// if empty line or error - skip
		if ((line[0] == '\n' && state == ELEMENTS) || error == -1)
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		// error = -1;
		t_parse_state type = identify_parse_state(line);
		// printf("line: %s, type: %d\n", line, type);
		//check all the elements first
		if (state == ELEMENTS)
		{
			// if got type is map return error
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
				// parse_map(line, data);
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
			write(2, "Invalid element in file\n", 25);
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
	// at the end validate the last part is map
	if (state == ELEMENTS)
		return (error_message("No map found"));
	return 1;
}
