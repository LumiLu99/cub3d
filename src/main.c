/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:55:26 by yelu              #+#    #+#             */
/*   Updated: 2026/01/04 22:21:37 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	update(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	print_fps(data);
	move_player(data);
	sprite_sway(data);
	ft_bzero(data->img_mlx.addr, WIDTH * HEIGHT
		* (data->img_mlx.bits_per_pixel / 8));
	draw_dda(data);
	print_minimap(data);
	print_player_pixel(data);
	draw_rays_minimap(data);
	draw_cat(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_mlx.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		print_error_exit("Usage: ./cub3D <map file.ber>\n");
		return (1);
	}
	if (init_data(&data, argv))
		return (1);
	mlx_hook(data.win, KeyPress, KeyPressMask, on_keypress, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, on_keyrelease, &data);
	mlx_hook(data.win, MotionNotify, PointerMotionMask, on_keymouse, &data);
	mlx_mouse_move(data.mlx, data.win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide(data.mlx, data.win);
	mlx_hook(data.win, DestroyNotify, SubstructureNotifyMask,
		ft_close, &data);
	mlx_loop_hook(data.mlx, update, &data);
	mlx_loop(data.mlx);
	return (0);
}

/**
 *  * The Core Idea: Simulating 3D with 2D
 Imagine you are standing in the middle of the map.
You can't see the whole map at once, only what's in your Field of View (FOV).

The program simulates this by sending out a series of "rays"
from your player's position across your FOV. For every single vertical column of
pixels on your screen, one ray is cast.

Each ray travels in a straight line until it hits a wall.

The program then does two things:

1) Measures the distance the ray traveled.

2) Based on that distance, it draws a vertical line in the 
corresponding column on the screen.

If the wall is close, the distance is short, so the 
vertical line is drawn very tall.
If the wall is far away, the distance is long, and the 
line is drawn short.
This creates the illusion of depth and perspective.
 */
