/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:19:53 by yelu              #+#    #+#             */
/*   Updated: 2025/11/06 22:48:05 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ray_init(t_data *data, int x)
{
	data->ray.camera_x = 2 * x / (double)(WIDTH) - 1;
	data->ray.ray_dir_x = data->player.dir_x + (data->player.plane_x * data->ray.camera_x);
	data->ray.ray_dir_y = data->player.dir_y + (data->player.plane_y * data->ray.camera_x);
	if (data->ray.ray_dir_x == 0)
        data->ray.delta_x = INFINITY;
    else
        data->ray.delta_x = fabs(1 / data->ray.ray_dir_x);
    if (data->ray.ray_dir_y == 0)
        data->ray.delta_y = INFINITY;
    else
        data->ray.delta_y = fabs(1 / data->ray.ray_dir_y);
	data->ray.map_x = (int)(data->player.pos_x);
	data->ray.map_y = (int)(data->player.pos_y);
}

void	side_dist(t_data *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.side_n_x = -1;
		data->ray.side_dist_x = (data->player.pos_x
				- data->ray.map_x) * data->ray.delta_x;
	}
	else
	{
		data->ray.side_n_x = 1;
		data->ray.side_dist_x = ((data->ray.map_x + 1) 
				- data->player.pos_x) * data->ray.delta_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.side_n_y = -1;
		data->ray.side_dist_y = (data->player.pos_y
				- data->ray.map_y) * data->ray.delta_y;
	}
	else
	{
		data->ray.side_n_y = 1;
		data->ray.delta_y = ((data->ray.map_y + 1)
				- data->player.pos_y) * data->ray.side_dist_y;
	}
}	

static void	dda_calc(t_data *data, int *side)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_x;
			data->ray.map_x += data->ray.side_n_x;
			*side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.side_dist_y;
			data->ray.map_y += data->ray.side_n_x;
			*side = 1;
		}
		if (data->map.map_arr[data->ray.map_x][data->ray.map_y] > 0)
			hit = 1;
		if (*side == 0)
			data->ray.perp_dist = (data->ray.map_x - data->player.pos_x
					+ (1 - data->ray.side_n_x) / 2) / data->ray.ray_dir_x;
		else
			data->ray.perp_dist = (data->ray.map_y - data->player.pos_y
					+ (1 - data->ray.side_n_y) / 2) / data->ray.ray_dir_y;
	}
}



void	draw_dda(t_data *data)
{
	int	x;
	int	side;

	x = 0;
	side = -1;
	while (x < WIDTH)
	{
		ray_init(data, x);
		side_dist(data);
		dda_calc(data, &side);
		x++;
	}
}
