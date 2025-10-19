/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:55:26 by yelu              #+#    #+#             */
/*   Updated: 2025/10/15 19:32:20 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
	dst = data->img.addr + (y * data->img.line_len + x * (data->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	trying(t_data *data)
{
	int i = 0;
	int j = 0;
	data->player.x = 200;
	data->player.y = 200;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			my_mlx_pixel_put(data, data->player.x + i, data->player.y + j, RED_PIXEL);
			j++;
		}
		i++;
	}
}

int	on_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_close(data);
	return (0);
}

int	ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

int main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	if (argc == 2)
	{
		init_data(&data);
		trying(&data);
		mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
		mlx_hook(data.win, KeyPress, KeyPressMask, on_keypress, &data);
		mlx_hook(data.win, DestroyNotify, SubstructureNotifyMask,
			ft_close, &data);
		mlx_loop(data.mlx);
	}
	else
		print_error_exit("Usage: ./cub3D <map file.ber>\n");
}
