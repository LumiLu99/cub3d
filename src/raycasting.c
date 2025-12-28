/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:19:53 by yelu              #+#    #+#             */
/*   Updated: 2025/12/28 20:21:43 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void ray_init(t_data *data, int x)
{
    data->ray.camera_x = (2 * x) / (double)(WIDTH) - 1;
    data->ray.ray_dir_x = data->player.dir_x + (data->player.plane_x * data->ray.camera_x);
    data->ray.ray_dir_y = data->player.dir_y + (data->player.plane_y * data->ray.camera_x);
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

static void dda_calc(t_data *data, int *side)
{
    int  hit;
    char tile;

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
    if (*side == 0)
        data->ray.perp_dist = (data->ray.map_x - data->player.pos_x
                + (1 - data->ray.side_n_x) / 2.0) / data->ray.ray_dir_x;
    else
        data->ray.perp_dist = (data->ray.map_y - data->player.pos_y
                + (1 - data->ray.side_n_y) / 2.0) / data->ray.ray_dir_y;
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

void ray_tex_wall(t_data *data, int x, int y)
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
		ray_tex_sides(data, side);
		ray_tex_draw(data, x);
		x++;
	}
}
