/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:42:28 by wshee             #+#    #+#             */
/*   Updated: 2025/11/30 22:31:38 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

int parse_texture(char *map_file)
{
	int fd = open_file(map_file);
	char *line = get_next_line(fd);
	while (line)
	{
		if (line[0] == ' ' || line[0] == '1' || line[0] == '0')
			break ;
		printf("line: %s\n", line);
		if (line[0] != '\n')
		{
			char **texture = ft_split(line, ' ');
			if (!texture)
			{
				ft_putstr_fd("Failed to split texture\n", 2);
				return 1;
			}
			int counter = 0;
			while (texture[counter])
				counter++;
			if (counter != 2)
				return 1;
			char *identifier = texture[0];
			printf("identifier: %s\n", identifier);
			char *texture_path = texture[1];
			printf("texture path: %s\n", texture_path);
			char *trim = ft_strtrim(texture_path, "\n");
			// TODO: different for floor and ceiling, check until texture only
			if(!check_file_ext(trim, ".xpm"))
				return 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	return 0;
}
