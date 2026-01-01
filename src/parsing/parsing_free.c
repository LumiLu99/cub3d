/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 13:18:42 by wshee             #+#    #+#             */
/*   Updated: 2026/01/01 15:24:40 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

void free_2d_array(char **array);
bool error_message(char *message);
void free_texture_path(t_data *data);
void cleanup_data(t_data *data);
void cleanup_texture(char **texture, char *texture_path);

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
	if(data->map.map_arr)
	{
		free_2d_array(data->map.map_arr);
		data->map.map_arr = NULL;
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

void print_2d_map(char **array)
{
	for (int i = 0; array[i] != NULL; i++)
	{
		printf("array[%d]: [", i);
		for (int j = 0; array[i][j] != '\0'; j++)
			printf("%c", array[i][j]);
		printf("]\n");
	}
}
