/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:03:12 by yelu              #+#    #+#             */
/*   Updated: 2026/01/02 14:07:27 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_player_pixel(t_data *data)
{
	int	i;
	int	j;
	
	i = -3;
	j = -3;
	while (i < 3)
	{
		j = -3;
		while (j < 3)
		{
			my_mlx_pixel_put(data, (data->player.pos_x * TILE_SIZE)
                + i, (data->player.pos_y * TILE_SIZE) + j, RED_PIXEL);
			j++;
		}
		i++;
	}
}
