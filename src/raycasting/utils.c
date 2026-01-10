/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:13:12 by yelu              #+#    #+#             */
/*   Updated: 2026/01/04 22:10:21 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_error_exit(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit (1);
}

int	ft_close(t_data *data)
{
	int	i;

	i = 0;
	cleanup_data(data);
	mlx_destroy_image(data->mlx, data->img_mlx.img);
	while (i < TEX_SIZE)
	{
		mlx_destroy_image(data->mlx, data->tex[i].img);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		mlx_destroy_image(data->mlx, data->sprite[i].img_ptr);
		i++;
	}
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	print_fps(t_data *data)
{
	data->time.time = get_time_in_ms();
	data->time.delta_time = (data->time.time - data->time.old_time) / 1000.0;
	data->time.old_time = data->time.time;
	data->time.fps_count++;
	if (data->time.time - data->time.start_time >= 1000)
	{
		data->time.fps = data->time.fps_count;
		printf("FPS: %d\n", data->time.fps);
		data->time.fps_count = 0;
		data->time.start_time = data->time.time;
	}
}

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->img_mlx.addr + (y * data->img_mlx.line_len
			+ x * (data->img_mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
