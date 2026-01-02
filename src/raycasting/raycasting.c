/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:19:53 by yelu              #+#    #+#             */
/*   Updated: 2026/01/03 00:16:29 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ray_init(t_data *data, int x)
{
	data->ray.camera_x = (2 * x) / (double)(WIDTH) - 1;
	data->ray.ray_dir_x = data->player.dir_x + (data->player.plane_x
			* data->ray.camera_x);
	data->ray.ray_dir_y = data->player.dir_y + (data->player.plane_y
			* data->ray.camera_x);
	if (data->ray.ray_dir_x == 0)
		data->ray.delta_x = 1e30;
	else
		data->ray.delta_x = fabs(1 / data->ray.ray_dir_x);
	if (data->ray.ray_dir_y == 0)
		data->ray.delta_y = 1e30;
	else
		data->ray.delta_y = fabs(1 / data->ray.ray_dir_y);
	data->ray.map_x = (int)(data->player.pos_x);
	data->ray.map_y = (int)(data->player.pos_y);
}

void	ray_tex_init(t_data *data)
{
	data->ray.wall_height = (int)(HEIGHT / data->ray.perp_dist);
	data->ray.draw_start = -data->ray.wall_height / 2 + HEIGHT / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.wall_height / 2 + (HEIGHT / 2);
	if (data->ray.draw_end >= HEIGHT)
		data->ray.draw_end = HEIGHT - 1;
}

void	draw_dda(t_data *data)
{
	int	x;
	int	side;

	side = -1;
	x = 0;
	while (x < WIDTH)
	{
		ray_init(data, x);
		side_dist(data);
		dda_calc(data, &side);
		ray_tex_init(data);
		ray_tex_sides(data, side);
		ray_tex_draw(data, x);
		x++;
	}
}
