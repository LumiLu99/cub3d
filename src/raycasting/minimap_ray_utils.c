/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_ray_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:57:55 by yelu              #+#    #+#             */
/*   Updated: 2026/01/02 23:03:49 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_line(t_data *data, double end_x, double end_y)
{
	double	dx;
	double	dy;
	double	x;
	double	y;
	double	step;

	x = data->player.pos_x * TILE_SIZE;
	y = data->player.pos_y * TILE_SIZE;
	dx = end_x - x;
	dy = end_y - y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	while (step >= 0)
	{
		my_mlx_pixel_put(data, x, y, RED_PIXEL);
		x += dx;
		y += dy;
		step--;
	}
}

static void	init_minimap_vars(t_minimap *ray, t_data *data, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
	ray->ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	calc_minimap_step(t_minimap *ray, t_data *data)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos_y)
			* ray->delta_dist_y;
	}
}

static void	perform_minimap_dda(t_minimap *ray, t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map.map_arr[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	process_minimap_ray(t_data *data, int x)
{
	t_minimap	ray;
	double		perp_wall_dist;
	double		end_x;
	double		end_y;

	init_minimap_vars(&ray, data, x);
	calc_minimap_step(&ray, data);
	perform_minimap_dda(&ray, data);
	if (ray.side == 0)
		perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
	else
		perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
	end_x = (data->player.pos_x + ray.ray_dir_x * perp_wall_dist)
		* TILE_SIZE;
	end_y = (data->player.pos_y + ray.ray_dir_y * perp_wall_dist)
		* TILE_SIZE;
	draw_line(data, end_x, end_y);
}
