/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:42:28 by wshee             #+#    #+#             */
/*   Updated: 2025/12/21 00:15:31 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

int	convert_rgb_to_int(const char *str)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			sum = (sum * 10) + (str[i] - 48);
			i++;
		}
		else
		{ 
			return -1;
		}
	}
	return (sum);
}

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
	// printf("counter: %d\n", counter);
	if (counter != 3)
		return (-1);
	// TODO: Modify atoi to check for alphabet
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
	printf("identifier: %s\n", identifier);
	if (ft_strlen(identifier) > 2)
	{
		return (error_message("Invalid type identifier"));
	}
	char *texture_path = ft_strtrim(texture[1], "\t\n");
	printf("texture path: %s\n", texture_path);
	int i = 0;
	while(i < 4)
	{
		if (ft_strncmp(identifier, texture_identifier[i], ft_strlen(identifier)) == 0)
		{
			data->tex[i].tex_path = ft_strdup(texture_path);
			// printf("%s\n", tex[i].tex_path);
			if (!check_file_ext(texture_path, ".xpm"))
				return (error_message("Invalid texture file: must be end with .xpm"));
		}
		i++;
	}
	if (ft_strlen(identifier) == 1 && (line[0] == 'F' || line[0] == 'C'))
	{
		int color = parse_color(identifier, texture_path); 
		if (color == -1)
		return (error_message("Invalid RGB color"));
		printf("color: %d\n", color);
		if (line[0] == 'F')
			data->map.floor = color;
		else
			data->map.ceiling = color;
	}
	// TODO: make sure every elements exist
	// TODO: free everything, write function free 2d array
	return 0;
}

bool check_all_element_exists(t_data *data)
{
	int i = 0;
	while (i < 4)
	{
		if (data->tex[i].tex_path == NULL)
			return(error_message("Texture elements given incomplete"));
	}
	if (data->map.floor == -1 || data->map.ceiling == -1)
		return(error_message("Floor and ceiling elements given incomplete"));
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

// TODO: divide into 2 different state (elements and state)
int parse_file(char *filename, t_data *data)
{
	t_parse_state	state;
	int result;
	
	state = ELEMENTS;
	result = 0;
	if (!check_file_ext(filename, ".cub"))
	{
		printf("Invalid map: map file extension must be \".cub\"\n");
		return 1;
	}
	int fd = open_file(filename);
	if (fd == -1)
		return (error_message("Invalid fd: Failed to open file"));
	char *line = get_next_line(fd);
	// TODO: after texture parse the map, try to think to continue with the map
	while (line)
	{
		// if empty line - skip
		if (line[0] == '\n')
		{
			continue;	
		}
		// result = -1;
		printf("line: %s\n", line);
		t_parse_state type = identify_parse_state(line);
		//check all the elements first
		if (state == ELEMENTS)
			// if got type is map return error
			if (!parse_texture(line, data))
				result = -1;
		// when check is map element (first line)
		// validate all the element had been complete
		// change the state to map
		// parse map
		if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
			parse_map();
		free(line);
		line = get_next_line(fd);
	}
	// at the end validate the last part is map
	// check if element return no map found
	close(fd);
	if (result == -1)
		return 1;
	if (!check_all_element_exists(data))
		return 1;
	return 0;
}
