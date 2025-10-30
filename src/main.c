/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:55:26 by yelu              #+#    #+#             */
/*   Updated: 2025/10/30 13:49:41 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->map.map_arr[0] = "11111111";
	data->map.map_arr[1] = "10000001";
	data->map.map_arr[2] = "10000011";
	data->map.map_arr[3] = "10010001";
	data->map.map_arr[4] = "10000001";
	data->map.map_arr[5] = "11000001";
	data->map.map_arr[6] = "10000001";
	data->map.map_arr[7] = "11111111";
	init_mlx(data);
	init_player(&data->player);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		print_error_exit("mlx init failed!\n");
	data->win = mlx_new_window(data->mlx, 1024, 764, "Cub3D");
	if (!data->win)
		print_error_exit("win init failed!\n");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.img)
		print_error_exit("img init failed!\n");
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, 
			&data->img.line_len, &data->img.endian);
	if (!data->img.addr)
		print_error_exit("img addr init failed!\n");
}


static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
	dst = data->img.addr + (y * data->img.line_len + x * (data->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	print_player_pixel(t_data *data)
{
	int i = 0;
	int j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(data, data->player.x + i, data->player.y + j, RED_PIXEL);
			j++;
		}
		i++;
	}
}

static void	print_minimap(t_data *data)
{
	int i = 0;
	int j = 0;
	int mx = 0;
	int my = 0;
	int x = 0;
	int y = 0;
	while (data->map.map_arr[i])
	{
		j = 0;
		while (data->map.map_arr[i][j])
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			if (data->map.map_arr[i][j] == '1')
			{
				mx = 0;
				while (mx < TILE_SIZE)
				{
					my = 0;
					while (my < TILE_SIZE)
					{
						my_mlx_pixel_put(data, x + mx, y + my, WHITE_PIXEL);
						my++;
					}
					mx++;
				}
			}
			else
			{
				mx = 0;
				while (mx < TILE_SIZE)
				{
					my = 0;
					while (my < TILE_SIZE)
					{
						my_mlx_pixel_put(data, x + mx, y + my, GRAY_PIXEL);
						my++;
					}
					mx++;
				}
			}
			j++;
		}
		i++;
	}
}

bool	touch(float px, float py, t_data *data)
{
	int	x;
	int	y;

	x = px / TILE_SIZE;
	y = py / TILE_SIZE;
	if (data->map.map_arr[y][x] == '1')
		return (true);
	return (false);
}

int	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_data *data)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;
	
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - data->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	draw_line(t_data *data, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	float	dist;
	float	height;
	int		start_y;
	int		end;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = data->player.x;
	ray_y = data->player.y;
	while (!touch(ray_x, ray_y, data))
	{
		my_mlx_pixel_put(data, ray_x, ray_y, GREEN_PIXEL);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	dist = fixed_dist(data->player.x, data->player.y, ray_x, ray_y, data);
	height = (TILE_SIZE / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		my_mlx_pixel_put(data, i, start_y, 0x0000FF);
		start_y++;
	}
	
}

static void draw_ray(t_data *data)
{
    int i;
    double ray_x;
    double ray_y;
	int map_x;
	int map_y;

    i = 0;
    while (i < WIDTH) // Draw a ray that is 30 pixels long for now
    {
        // Calculate the point on the ray at distance 'i'
        ray_x = data->player.x + i * cos(data->player.angle);
        ray_y = data->player.y + i * sin(data->player.angle);
		map_x = (int)ray_x / TILE_SIZE;
		map_y = (int)ray_y / TILE_SIZE;
		my_mlx_pixel_put(data, ray_x, ray_y, GREEN_PIXEL); // Use a bright color like yellow
		if (data->map.map_arr[map_y][map_x] == '1')
			break ;
		i++;
        // Draw the pixel for this point on the ray
    }
}

int	update(void *param)
{
	t_data	*data;
	// float	fraction;
	// float	start_x;
	// int		i;
	
	data = (t_data *)param;
	move_player(data);
	ft_bzero(data->img.addr, WIDTH * HEIGHT * (data->img.bits_per_pixel / 8));
	print_minimap(data);
	print_player_pixel(data);
	// fraction = PI / 3 / WIDTH;
	// // fraction = PI / 3 / WIDTH;: You define a Field of View of 60 degrees (PI / 3 radians). 
	// // This line calculates the tiny angle difference between each of the rays you will cast.
	// start_x = data->player.angle - PI / 6;
	// // calculate the angle for the very first ray, which is on the far-left side of your FOV (player's angle minus 30 degrees).
	// i = 0;
	// while (i < WIDTH)
	// {
	// 	draw_line(data, start_x, i);
	// 	start_x += fraction;
	// 	i++;
	// }
	draw_ray(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}


int main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	if (argc == 2)
	{
		init_data(&data);
		mlx_hook(data.win, KeyPress, KeyPressMask, on_keypress, &data);
		mlx_hook(data.win, KeyRelease, KeyReleaseMask, on_keyrelease, &data);
		mlx_loop_hook(data.mlx, update, &data);
		mlx_hook(data.win, DestroyNotify, SubstructureNotifyMask,
			ft_close, &data);
		mlx_loop(data.mlx);
	}
	else
		print_error_exit("Usage: ./cub3D <map file.ber>\n");
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