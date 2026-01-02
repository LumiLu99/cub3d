/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 23:10:37 by yelu              #+#    #+#             */
/*   Updated: 2026/01/02 23:33:21 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ray_tex_sides(t_data *data, int side)
{
	data->ray.wall_x = data->player.pos_x + data->ray.perp_dist * data->ray.ray_dir_x;
	if (!side)
		data->ray.wall_x = data->player.pos_y + data->ray.perp_dist * data->ray.ray_dir_y;
	data->ray.wall_x -= floor(data->ray.wall_x);
	if (!side)
	{
		if (data->ray.ray_dir_x > 0)
			data->ray.side = EAST;
		else
			data->ray.side = WEST;
	}
	else
	{
		if (data->ray.ray_dir_y > 0)
			data->ray.side = SOUTH;
		else
			data->ray.side = NORTH;
	}
	data->ray.tex_num = (int)(data->ray.wall_x * (double)(data->tex[data->ray.side].img_width));
	if ((!side && data->ray.ray_dir_x > 0)
		|| (side && data->ray.ray_dir_y < 0))
		data->ray.tex_num = data->tex[data->ray.side].img_width - data->ray.tex_num - 1;
}

void    ray_tex_wall(t_data *data, int x, int y)
{
	int wall_step;
	int	tex_y;
	unsigned int	color;

	wall_step = y * 2 - HEIGHT + data->ray.wall_height;
	tex_y = (wall_step * data->tex[data->ray.side].img_height)
		/ (2 * data->ray.wall_height);
	color = *((unsigned int *)(data->tex[data->ray.side].addr
			+ (tex_y * data->tex[data->ray.side].line_len
				+ data->ray.tex_num * (data->tex[data->ray.side].bits_per_pixel / 8))));
	my_mlx_pixel_put(data, x, y, color);
}

void	ray_tex_draw(t_data *data, int x)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < data->ray.draw_start)
		{
			my_mlx_pixel_put(data, x, y, data->map.ceiling);
		}
		else if (y <= data->ray.draw_end)
			ray_tex_wall(data, x, y);
		else
			my_mlx_pixel_put(data, x, y, data->map.floor);
		y++;
	}
}
