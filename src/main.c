/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:55:26 by yelu              #+#    #+#             */
/*   Updated: 2025/10/21 19:25:39 by yelu             ###   ########.fr       */
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
	while (i < 10)
	{
		j = 0;
		while (j < 10)
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
	dist = distance(ray_x - data->player.x, ray_y - data->player.y);
	height = (TILE_SIZE / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		my_mlx_pixel_put(data, i, start_y, 0x0000FF);
		start_y++;
	}
	
}

int	update(void *param)
{
	t_data	*data;
	// float	ray_x;
	// float	ray_y;
	// float	cos_angle;
	// float	sin_angle;
	float	fraction;
	float	start_x;
	int		i;
	
	data = (t_data *)param;
	move_player(data);
	ft_bzero(data->img.addr, WIDTH * HEIGHT * (data->img.bits_per_pixel / 8));
	print_minimap(data);
	print_player_pixel(data);
	// ray_x = data->player.x;
	// ray_y = data->player.y;
	// cos_angle = cos(data->player.angle);
	// sin_angle = sin(data->player.angle);
	fraction = PI / 3 / WIDTH;
	start_x = data->player.angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(data, start_x, i);
		start_x += fraction;
		i++;
	}
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
