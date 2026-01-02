/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:55:26 by yelu              #+#    #+#             */
/*   Updated: 2026/01/02 17:15:11 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void draw_line(t_data *data, double x1, double y1, double x2, double y2)
{
    double delta_x = x2 - x1;
    double delta_y = y2 - y1;
    double step = (fabs(delta_x) > fabs(delta_y)) ? fabs(delta_x) : fabs(delta_y);

    double dx = delta_x / step;
    double dy = delta_y / step;

    double x = x1;
    double y = y1;
    int i = 0;

    while (i <= step)
    {
        my_mlx_pixel_put(data, x, y, RED_PIXEL);
        x += dx;
        y += dy;
        i++;
    }
}

void draw_rays_minimap(t_data *data)
{
    int x = 0;


    while (x < WIDTH)
    {

        double camera_x = 2 * x / (double)WIDTH - 1;
        double ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
        double ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;


        int map_x = (int)data->player.pos_x;
        int map_y = (int)data->player.pos_y;

        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

        double side_dist_x;
        double side_dist_y;
        int step_x;
        int step_y;
        int hit = 0;
        int side;


        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (data->player.pos_x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - data->player.pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (data->player.pos_y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - data->player.pos_y) * delta_dist_y;
        }
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (data->map.map_arr[map_y][map_x] == '1')
                hit = 1;
        }
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (side_dist_x - delta_dist_x);
        else
            perp_wall_dist = (side_dist_y - delta_dist_y);


        double start_x = data->player.pos_x * TILE_SIZE;
        double start_y = data->player.pos_y * TILE_SIZE;

        double end_x = (data->player.pos_x + ray_dir_x * perp_wall_dist) * TILE_SIZE;
        double end_y = (data->player.pos_y + ray_dir_y * perp_wall_dist) * TILE_SIZE;

        draw_line(data, start_x, start_y, end_x, end_y);

        x += 1;
    }
}

int	update(void *param)
{
	t_data	*data;
	data = (t_data *)param;
	print_fps(data);
	move_player(data);
	ft_bzero(data->img_mlx.addr, WIDTH * HEIGHT * (data->img_mlx.bits_per_pixel / 8));
	draw_dda(data);
	print_minimap(data);
	print_player_pixel(data);
	draw_rays_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_mlx.img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	if (argc != 2)
	{
		print_error_exit("Usage: ./cub3D <map file.ber>\n");
		return (1);
	}
	if (init_data(&data, argv))
		return (1);
	mlx_hook(data.win, KeyPress, KeyPressMask, on_keypress, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, on_keyrelease, &data);
	// mlx_mouse_move(data.mlx, data.win, WIDTH / 2, HEIGHT / 2);
	// mlx_hook(data.win, MotionNotify, PointerMotionMask, key_mouse, &data);
	mlx_hook(data.win, DestroyNotify, SubstructureNotifyMask,
		ft_close, &data);
	mlx_loop_hook(data.mlx, update, &data);
	mlx_loop(data.mlx);
	return 0;
}

/**
 * The Core Idea: Simulating 3D with 2D
Imagine you are standing in the middle of the map.
You can't see the whole map at once, only what's in your Field of View (FOV).

The program simulates this by sending out a series of "rays"
from your player's position across your FOV. For every single vertical column of
pixels on your screen, one ray is cast.

Each ray travels in a straight line until it hits a wall.

The program then does two things:

1) Measures the distance the ray traveled.

2) Based on that distance, it draws a vertical line in the corresponding column on the screen.

If the wall is close, the distance is short, so the vertical line is drawn very tall.
If the wall is far away, the distance is long, and the line is drawn short.
This creates the illusion of depth and perspective.
 */
