/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:08:16 by yelu              #+#    #+#             */
/*   Updated: 2026/01/05 18:41:48 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_data(t_data *data, char **argv)
{
	ft_bzero(data, sizeof(t_data));
	data->map.floor = -1;
	data->map.ceiling = -1;
	if (!parse_file(argv[1], data))
	{
		cleanup_data(data);
		return (1);
	}
	if (!parse_map(argv[1], data))
	{
		cleanup_data(data);
		return (1);
	}
	init_mlx(data);
	init_player(&data->player);
	tex_init(data);
	sprite_init(data);
	return (0);
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
	data->img_mlx.addr = mlx_get_data_addr(data->img_mlx.img,
			&data->img_mlx.bits_per_pixel,
			&data->img_mlx.line_len, &data->img_mlx.endian);
	if (!data->img_mlx.addr)
		print_error_exit("img addr init failed!\n");
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
