/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:03:12 by yelu              #+#    #+#             */
/*   Updated: 2026/01/02 16:14:52 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_player_pixel(t_data *data)
{
	int	i;
	int	j;
	
	i = -3;
	j = -3;
	while (i < 3)
	{
		j = -3;
		while (j < 3)
		{
			my_mlx_pixel_put(data, (data->player.pos_x * TILE_SIZE)
                + i, (data->player.pos_y * TILE_SIZE) + j, RED_PIXEL);
			j++;
		}
		i++;
	}
}

static void	check_wall(t_data *data, int *i, int *j, int *x, int *y)
{
	int	mx;
	int	my;

	if (data->map.map_arr[*i][*j] == '1')
	{
		mx = 0;
		while (mx < TILE_SIZE)
		{
			my = 0;
			while (my < TILE_SIZE)
			{
				my_mlx_pixel_put(data, *x + mx, *y + my, GRAY_PIXEL);
				my++;
			}
			mx++;
		}
	}
}

static void	check_floor(t_data *data, int *i, int *j, int *x, int *y)
{
	int	mx;
	int	my;

	if (data->map.map_arr[*i][*j] == '0' || data->map.map_arr[*i][*j] == 'N' ||
		data->map.map_arr[*i][*j] == 'S' || data->map.map_arr[*i][*j] == 'E' ||
		data->map.map_arr[*i][*j] == 'W')
	{
		mx = 0;
		while (mx < TILE_SIZE)
		{
			my = 0;
			while (my < TILE_SIZE)
			{
				my_mlx_pixel_put(data, *x + mx, *y + my, WHITE_PIXEL);
				my++;
			}
			mx++;
		}
	}
}

void	print_minimap(t_data *data)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	while (data->map.map_arr[i])
	{
		j = 0;
		while (data->map.map_arr[i][j])
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			check_wall(data, &i, &j, &x, &y);
			check_floor(data, &i, &j, &x, &y);
			j++;
		}
		i++;
	}
}
