/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 13:18:42 by wshee             #+#    #+#             */
/*   Updated: 2025/12/28 15:43:42 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

void free_2d_array(char **array)
{
	int i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
}

bool error_message(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	return false;
}

bool check_file_ext(const char *filename, const char *ext)
{
	size_t filename_len = ft_strlen(filename);
	size_t ext_len = ft_strlen(ext);

	if (filename[0] == '\0')
		return false;
	if (filename_len <= ext_len)
		return false;
	while (filename[filename_len - 1] && ext_len > 0)
	{
		// printf("filename[%c], ext[%c]\n", filename[filename_len - 1], ext[ext_len - 1]);
		if (filename[filename_len - 1] != ext[ext_len - 1])
			return false;
		// printf("filename_len: %zu, ext: %zu\n", filename_len, ext_len);
		filename_len--;
		ext_len--;
	}
	return true;
}

void free_texture_path(t_data *data)
{
	int i = 0;
	while (i < 4)
	{
		if (data->tex[i].tex_path)
		{
			free(data->tex[i].tex_path);
			data->tex[i].tex_path = NULL;
		}
		i++;
	}
}

void cleanup_data(t_data *data)
{
	free_texture_path(data);
	if(data->map.array)
	{
		free_2d_array(data->map.array);
		data->map.array = NULL;
	}
}

void cleanup_texture(char **texture, char *texture_path)
{
	if (texture)
	{
		free_2d_array(texture);
		texture = NULL;
	}
	if(texture_path)
	{
		free(texture_path);
		texture_path = NULL;
	}
}
