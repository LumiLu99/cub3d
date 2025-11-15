/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:55:26 by yelu              #+#    #+#             */
/*   Updated: 2025/11/15 22:34:59 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_data(t_data *data)
{
	int i = 0;
	ft_bzero(data, sizeof(t_data));
	data->map.map_arr[0] = "11111111111";
	data->map.map_arr[1] = "11110000001";
	data->map.map_arr[2] = "10000000001";
	data->map.map_arr[3] = "10000011001";
	data->map.map_arr[4] = "10000000001";
	data->map.map_arr[5] = "10000000001";
	data->map.map_arr[6] = "10000000001";
	data->map.map_arr[7] = "10000000001";
	data->map.map_arr[8] = "10000000001";
	data->map.map_arr[9] = "10000000001";
	data->map.map_arr[10] = "10000000001";
	data->map.map_arr[11] = "10000000001";
	data->map.map_arr[12] = "10000000001";
	data->map.map_arr[13] = "11111111111";
	while (i < TEX_SIZE)
	{
		data->tex[i].tex_path = "textures/greystone.xpm";
		i++;
	}
	init_mlx(data);
	init_player(&data->player);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		print_error_exit("mlx init failed!\n");
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		print_error_exit("win init failed!\n");
	data->img_mlx.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img_mlx.img)
		print_error_exit("img_mlx init failed!\n");
	data->img_mlx.addr = mlx_get_data_addr(data->img_mlx.img, &data->img_mlx.bits_per_pixel, 
			&data->img_mlx.line_len, &data->img_mlx.endian);
	if (!data->img_mlx.addr)
		print_error_exit("img addr init failed!\n");
}

void	init_player(t_player *player)
{
	player->pos_x = 4.5;
	player->pos_y = 6.5;
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.66;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	init_fps(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->time.time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	data->time.old_time = data->time.time;
	data->time.start_time = data->time.time;
	data->time.delta_time = 0.0;
	data->time.fps_count = 0;
	data->time.fps = 0;
}


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
	dst = data->img_mlx.addr + (y * data->img_mlx.line_len + x * (data->img_mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	print_player_pixel(t_data *data)
{
	int i = 0;
	int j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			my_mlx_pixel_put(data, (data->player.pos_x * TILE_SIZE) + i, (data->player.pos_y * TILE_SIZE) + j, RED_PIXEL);
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
	mlx_put_image_to_window(data->mlx, data->win, data->img_mlx.img, 0, 0);
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
		mlx_hook(data.win, DestroyNotify, SubstructureNotifyMask,
			ft_close, &data);
		mlx_loop_hook(data.mlx, update, &data);
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