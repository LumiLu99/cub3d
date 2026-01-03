/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:55:26 by yelu              #+#    #+#             */
/*   Updated: 2026/01/03 21:09:28 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	on_keymouse(int x, int y, t_data *data)
{
	double	rot_speed;
	int		dx;
	double	sensitivity;
	
	(void)y;
	sensitivity = 0.0001;
	dx = x - (WIDTH / 2);
	if (dx != 0)
	{
		rot_speed = dx * sensitivity;
		rotate_player(data, rot_speed);
		mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
	}
	return (0);
}
	
static int get_pixel_color(t_sprite *sprite, int x, int y)
	{
		char    *ptr;
		int     color;
		
		// Boundary check to prevent Segmentation Faults
		if (x < 0 || x >= sprite->width || y < 0 || y >= sprite->height)
        return (0);
		
		// Find the address of the pixel
		ptr = sprite->addr + (y * sprite->line_length + x * (sprite->bits_per_pixel / 8));
		
		// Cast the pointer to an unsigned int to grab all 4 bytes (the color) at once
		color = *(unsigned int *)ptr;
		
		return (color);
	}
	
static void draw_torch(t_data *data)
{
    int x;
    int y;
    int color;
    
    // Round the floats to integers for pixel placement
    int screen_x = (int)data->sprite.x;
    int screen_y = (int)data->sprite.y;

    y = 0;
    while (y < data->sprite.height)
    {
        x = 0;
        while (x < data->sprite.width)
        {
            // Only draw if within screen boundaries to prevent segfaults
            if (screen_x + x >= 0 && screen_x + x < WIDTH &&
                screen_y + y >= 0 && screen_y + y < HEIGHT)
            {
                color = get_pixel_color(&data->sprite, x, y);
                // Adjust this transparency check based on your XPM (0 is usually transparent)
                if ((color & 0x00FFFFFF) != 0)
                    my_mlx_pixel_put(data, screen_x + x, screen_y + y, color);
            }
            x++;
        }
        y++;
    }
}

static void	sprite_sway(t_data *data)
{
	static float angle = 0;
	if (data->player.key_up || data->player.key_down || data->player.key_right || data->player.key_left)
    {
		angle += 0.15; // The speed of your steps
			
		// Horizontal: Sways once per "cycle" (Left to Right)
		int base_x = (WIDTH / 2) - (data->sprite.width / 2);
		data->sprite.x = base_x + (sin(angle) * 20.0);

		// Vertical: Bobs twice per "cycle" (Up and Down for EACH step)
		// By multiplying angle by 2, it completes two bobs for every one sway
		int base_y = HEIGHT - data->sprite.height + 20;
		data->sprite.y = base_y + (sin(angle * 2.0) * 10.0);
    }
	else
	{
		// A smoother way to "rest" the torch:
		// Instead of multiplying angle, we slowly move the current X/Y back to base
		data->sprite.x += ((WIDTH / 2 - data->sprite.width / 2) - data->sprite.x) * 0.1;
		data->sprite.y += ((HEIGHT - data->sprite.height) - data->sprite.y) * 0.1;
		
		// Optional: Reset angle to 0 when practically still to prevent value overflow
		if (fabs(data->sprite.x - (WIDTH / 2 - data->sprite.width / 2)) < 0.1)
			angle = 0;
	}
}

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
	draw_torch(data);
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
