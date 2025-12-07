/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:42:28 by wshee             #+#    #+#             */
/*   Updated: 2025/12/07 22:04:31 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

bool error_message(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	return false;
}

int parse_calour(char *identifier, char *color, t_img *tex)
{
	char **rgb = ft_split(color, ',');
	int counter = 0;
	while (rgb[counter])
		counter++;
	if (counter != 3)
		return (error_message("Invalid RGB color"));
	int r = ft_atoi(rgb[0]);
	int g = ft_atoi(rgb[1]);
	int b = ft_atoi(rgb[2]);
	// convert into hex
	return 0;
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
		return 1;
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
		if (parse_color(identifier, texture_path, tex))
			return 1;
	}
	// free everything, write function free 2d array
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
		if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
			break ;
		printf("line: %s\n", line);
		if (line[0] != '\n')
		{
			if (line[0] == 'N' || line[0] == 'W' || line[0] == 'S' || line[0] == 'E' || line[0] == 'F' || line[0] == 'C')
				if (parse_texture(line, tex))
					return 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	return 0;
}
