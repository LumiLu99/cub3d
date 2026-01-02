/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 23:10:47 by yelu              #+#    #+#             */
/*   Updated: 2026/01/02 23:38:52 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		data->ray.side_dist_x = (data->ray.map_x + 1.0
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
		data->ray.side_dist_y = (data->ray.map_y + 1.0
				- data->player.pos_y) * data->ray.delta_y;
	}
}

static void	perp_dist(t_data *data, int side)
{
	if (side == 0)
		data->ray.perp_dist = (data->ray.map_x - data->player.pos_x
				+ (1 - data->ray.side_n_x) / 2.0) / data->ray.ray_dir_x;
	else
		data->ray.perp_dist = (data->ray.map_y - data->player.pos_y
				+ (1 - data->ray.side_n_y) / 2.0) / data->ray.ray_dir_y;
}

void	dda_calc(t_data *data, int *side)
{
	int		hit;
	char	tile;

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
			data->ray.side_dist_y += data->ray.delta_y;
			data->ray.map_y += data->ray.side_n_y;
			*side = 1;
		}
		tile = data->map.map_arr[data->ray.map_y][data->ray.map_x];
		if (tile == '1' || tile == ' ')
			hit = 1;
	}
	perp_dist(data, *side);
}
