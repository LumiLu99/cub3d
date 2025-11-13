/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:19:53 by yelu              #+#    #+#             */
/*   Updated: 2025/11/11 18:50:03 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ray_init(t_data *data, int x)
{
	data->ray.camera_x = (2 * x) / (double)(WIDTH) - 1;
	data->ray.ray_dir_x = data->player.dir_x + (data->player.plane_x * data->ray.camera_x);
	data->ray.ray_dir_y = data->player.dir_y + (data->player.plane_y * data->ray.camera_x);
    data->ray.delta_x = fabs(1 / data->ray.ray_dir_x);
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
			data->ray.side_dist_y += data->ray.delta_y;
			data->ray.map_y += data->ray.side_n_y;
			*side = 1;
		}
		if (data->map.map_arr[data->ray.map_y][data->ray.map_x] != '0')
			hit = 1;
		if (*side == 0)
			data->ray.perp_dist = (data->ray.map_x - data->player.pos_x
					+ (1 - data->ray.side_n_x) / 2.0) / data->ray.ray_dir_x;
		else
			data->ray.perp_dist = (data->ray.map_y - data->player.pos_y
					+ (1 - data->ray.side_n_y) / 2.0) / data->ray.ray_dir_y;
	}
}

// void	calc_dda(t_data *data)
// {
// 	int i = 0;
// 	printf("Coming in calc_dda\n");
// 	while (data->ray.hit == 0)
// 	{
// 		printf("Entered while loop start calc_dda\n");
// 		if (data->ray.side_dist_x < data->ray.side_dist_y)
// 		{
// 			data->ray.side_dist_x += data->ray.delta_x;
// 			data->ray.map_x += data->ray.side_n_x;
// 			if (data->ray.side_n_x == -1)
// 				data->ray.side = EAST;
// 			else
// 				data->ray.side = WEST;
// 		}
// 		else
// 		{
// 			data->ray.side_dist_y += data->ray.delta_y;
// 			data->ray.map_y += data->ray.side_n_y;
// 			if (data->ray.side_n_y == -1)
// 				data->ray.side = SOUTH;
// 			else
// 				data->ray.side = NORTH;
// 		}
// 		printf("Map y: %d, Map x: %d\n", data->ray.map_y, data->ray.map_y);
// 		if (data->map.map_arr[data->ray.map_y][data->ray.map_x] == '1')
// 			data->ray.hit = 1;
// 		if (i > 1000)
// 			data->ray.hit = 1;
// 		printf("%d", i);
// 	}
// 	printf("Leaving calc_dda");
// }

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

void	ray_tex_draw(t_data *data, int x)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < data->ray.draw_start)
		{
			my_mlx_pixel_put(data, x, y, WHITE_PIXEL);
		}
		else if (y <= data->ray.draw_end)
			my_mlx_pixel_put(data, x, y, BLUE_PIXEL);
		else
			my_mlx_pixel_put(data, x, y, GRAY_PIXEL);
		y++;
	}
}

void	draw_dda(t_data *data)
{
	int	x;
	int side = -1;

	x = 0;
	while (x < WIDTH)
	{
		ray_init(data, x);
		side_dist(data);
		dda_calc(data, &side);
		ray_tex_init(data);
		ray_tex_draw(data, x);
		x++;
	}
}
