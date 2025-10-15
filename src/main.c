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

static void	init_shit(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	// char *map_init[6] = 
	// {
	// 	"11111",
	// 	"10001",
	// 	"10001",
	// 	"10001",
	// 	"11111",
	// 	NULL,
	// };
	// for (int i = 0; i < 6; i++)
	// 	strcpy(data->map[i], map_init[i]);
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
			mlx_pixel_put(data->mlx, data->win, data->player.x + i, data->player.y + j, RED_PIXEL);
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
		init_shit(&data);
		data.mlx = mlx_init();
		if (!data.mlx)
			return (1);
		data.win = mlx_new_window(data.mlx, 1024, 764, "Cub3D");
		if (!data.win)
			return (1);
		trying(&data);
		mlx_hook(data.win, KeyPress, KeyPressMask, on_keypress, &data);
		mlx_hook(data.win, DestroyNotify, SubstructureNotifyMask,
			ft_close, &data);
		mlx_loop(data.mlx);
	}
	else
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map file.ber>", 2);
		exit(1);
	}
}
