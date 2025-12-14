/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:42:28 by wshee             #+#    #+#             */
/*   Updated: 2025/12/14 22:59:09 by wshee            ###   ########.fr       */
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

int parse_color(char *identifier, char *color, t_img *tex)
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

int parse_texture(char *line, t_img *tex)
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
			tex[i].tex_path = ft_strdup(texture_path);
			// printf("%s\n", tex[i].tex_path);
			if (!check_file_ext(texture_path, ".xpm"))
				return (error_message("Invalid texture file: must be end with .xpm"));
		}
		i++;
	}
	// TODO: different for floor and ceiling, check until texture only
	if (ft_strlen(identifier) == 1 && (line[0] == 'F' || line[0] == 'C'))
	{
		int color = parse_color(identifier, texture_path, tex); 
		if (color == -1)
			return (error_message("Invalid RGB color"));
		printf("color: %d\n", color);
	}
	// TODO: make sure every elements exist
	// TODO: free everything, write function free 2d array
	return 0;
}

int parse_cub(char *filename, t_img *tex)
{
	if (!check_file_ext(filename, ".cub"))
	{
		printf("Invalid map: map file extension must be \".ext\"\n");
		return 1;
	}
	int fd = open_file(filename);
	char *line = get_next_line(fd);
	while (line)
	{
		// TODO: after texture parse the map, try to think to continue with the map
		if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
			break ;
		printf("line: %s\n", line);
		if (line[0] != '\n')
		{
			if (line[0] == 'N' || line[0] == 'W' || line[0] == 'S' || line[0] == 'E' || line[0] == 'F' || line[0] == 'C')
				if (!parse_texture(line, tex))
					return 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	return 0;
}
