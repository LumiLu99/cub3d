/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:52:51 by yelu              #+#    #+#             */
/*   Updated: 2025/12/31 16:27:24 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	tex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < TEX_SIZE)
	{
		if (!data->tex[i].tex_path)
			print_error_exit("Texture path empty\n");
		data->tex[i].img = mlx_xpm_file_to_image(data->mlx,
				data->tex[i].tex_path, &data->tex[i].img_width,
				&data->tex[i].img_height);
		if (!data->tex[i].img)
			print_error_exit("Failed to init xpm to image\n");
		data->tex[i].addr = mlx_get_data_addr(data->tex[i].img,
				&data->tex[i].bits_per_pixel, &data->tex[i].line_len,
				&data->tex[i].endian);
		if (!data->tex[i].addr)
			print_error_exit("Failed to init image addr\n");
		i++;
	}
}
