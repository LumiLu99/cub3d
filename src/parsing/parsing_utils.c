/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:46:31 by wshee             #+#    #+#             */
/*   Updated: 2026/01/02 13:59:49 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		identify_state(char c);
bool	check_open_file(const char *file, const char *ext, int *fd, char *msg);
bool	check_all_element_exists(t_data *data);
bool	check_file_ext(const char *filename, const char *ext);

int	identify_state(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E' || c == 'F' || c == 'C')
		return (ELEMENTS);
	else if (c == ' ' || c == '1' || c == '0')
		return (MAP);
	return (INVALID);
}

bool	check_open_file(const char *file, const char *ext, int *fd, char *msg)
{
	if (!check_file_ext(file, ext))
		return (error_message(msg));
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		return (error_message("Invalid fd or path: Failed to open file"));
	return (true);
}

bool	check_all_element_exists(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->tex[i].tex_path == NULL)
			return (error_message("Texture elements given incomplete"));
		i++;
	}
	if (data->map.floor == -1 || data->map.ceiling == -1)
		return (error_message("Floor and ceiling elements given incomplete"));
	return (true);
}

bool	check_file_ext(const char *filename, const char *ext)
{
	size_t	filename_len;
	size_t	ext_len;

	filename_len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (filename[0] == '\0')
		return (false);
	if (filename_len <= ext_len)
		return (false);
	while (filename[filename_len - 1] && ext_len > 0)
	{
		if (filename[filename_len - 1] != ext[ext_len - 1])
			return (false);
		filename_len--;
		ext_len--;
	}
	return (true);
}
