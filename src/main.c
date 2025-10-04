/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:55:26 by yelu              #+#    #+#             */
/*   Updated: 2025/10/04 18:07:19 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_init(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	char *map_init[6] = 
	{
		"11111",
		"10001",
		"10001",
		"10001",
		"11111",
		""
	};
	for (int i = 0; i < 6; i++)
		strcpy(data->map[i], map_init[i]);
}

int	on_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_close(data);
	return (0);
}

int	ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

int main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	if (argc == 2)
	{
		map_init(&data);
		data.mlx_ptr = mlx_init();
		if (!data.mlx_ptr)
			return (1);
		data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600, "Cub3D");
		if (!data.win_ptr)
			return (1);
		mlx_hook(data.win_ptr, KeyPress, KeyPressMask, on_keypress, &data);
		mlx_hook(data.win_ptr, DestroyNotify, SubstructureNotifyMask,
			ft_close, &data);
		mlx_loop(data.mlx_ptr);
	}
	else
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map file.ber>", 2);
		exit(1);
	}
}
