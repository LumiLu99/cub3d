/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:07:32 by yelu              #+#    #+#             */
/*   Updated: 2026/01/10 14:14:15 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Boundary check to prevent Segmentation Faults
// Find the address of the pixel
// Cast the pointer to an unsigned int to grab all 4 bytes (the color) at once
int	get_pixel_color(t_sprite *sprite, int x, int y)
{
	char	*ptr;
	int		color;

	if (x < 0 || x >= sprite->width || y < 0 || y >= sprite->height)
		return (0);
	ptr = sprite->addr + (y * sprite->line_length
			+ x * (sprite->bits_per_pixel / 8));
	color = *(unsigned int *)ptr;
	return (color);
}

static void	check_transparency(t_data *data, int x, int y, int idx)
{
	int	color;

	color = get_pixel_color(&data->sprite[idx], x, y);
	if ((color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(data, (int)data->sprite[idx].x + x,
			(int)data->sprite[idx].y + y, color);
}

void	draw_cat(t_data *data)
{
	int			x;
	int			y;
	int			color;
	int			idx;

	if (sin(data->player.sway_angle) > 0)
		idx = 0;
	else
		idx = 1;
	y = -1;
	while (++y < data->sprite[idx].height)
	{
		x = -1;
		while (++x < data->sprite[idx].width)
		{
			if ((int)data->sprite[idx].x + x >= 0
				&& (int)data->sprite[idx].x + x < WIDTH
				&& (int)data->sprite[idx].y + y >= 0
				&& (int)data->sprite[idx].y + y < HEIGHT)
			{
				check_transparency(data, x, y, idx);
			}
		}
	}
}

void	sprite_sway(t_data *data)
{
	int	pos_x;
	int	pos_y;

	pos_x = (WIDTH / 2) - (data->sprite[0].width / 2);
	pos_y = HEIGHT - data->sprite[0].height + 280;
	data->player.sway_angle += 0.15;
	if (data->player.sway_angle > 2.0 * PI)
		data->player.sway_angle -= 2.0 * PI;
	if (data->player.key_up || data->player.key_down
		|| data->player.key_right || data->player.key_left)
	{
		data->sprite[0].x = pos_x + (sin(data->player.sway_angle) * 20.0);
		data->sprite[0].y = pos_y + (sin(data->player.sway_angle * 2.0) * 10.0);
	}
	else
	{
		data->sprite[0].x += (pos_x - data->sprite[0].x) * (0.1);
		data->sprite[0].y += (pos_y - data->sprite[0].y) * (0.1);
	}
	data->sprite[1].x = data->sprite[0].x;
	data->sprite[1].y = data->sprite[0].y;
}
