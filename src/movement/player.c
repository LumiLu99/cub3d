/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:54:53 by yelu              #+#    #+#             */
/*   Updated: 2025/12/31 16:27:13 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_tile(t_data *data, int x, int y)
{
	if (y < 0 || !data->map.map_arr[y])
		return (0);
	if (x < 0 || x >= (int)ft_strlen(data->map.map_arr[y]))
		return (0);
	if (data->map.map_arr[y][x] == '1' || data->map.map_arr[y][x] == ' ')
		return (0);
	return (1);
}

static int	check_collision(t_data *data, double x, double y)
{
	double	buffer;

	buffer = 0.05;
	if (!is_valid_tile(data, (int)(x - buffer), (int)(y - buffer)))
		return (0);
	if (!is_valid_tile(data, (int)(x + buffer), (int)(y - buffer)))
		return (0);
	if (!is_valid_tile(data, (int)(x - buffer), (int)(y + buffer)))
		return (0);
	if (!is_valid_tile(data, (int)(x + buffer), (int)(y + buffer)))
		return (0);
	return (1);
}

static void	directional_key(t_data *data)
{
	double	rot_speed;

	rot_speed = 0.03;
	if (data->player.left_rotate)
	{
		double old_dir_x = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(-rot_speed)
			- data->player.dir_y * sin(-rot_speed);
		data->player.dir_y = old_dir_x * sin(-rot_speed) + data->player.dir_y * cos(-rot_speed);
		double old_plane_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(-rot_speed)
			- data->player.plane_y * sin(-rot_speed);
		data->player.plane_y = old_plane_x * sin(-rot_speed) + data->player.plane_y * cos(-rot_speed);
	}
	if (data->player.right_rotate)
	{
		double old_dir_x = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(rot_speed)
			- data->player.dir_y * sin(rot_speed);
		data->player.dir_y = old_dir_x * sin(rot_speed) + data->player.dir_y * cos(rot_speed);
		double old_plane_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(rot_speed)
			- data->player.plane_y * sin(rot_speed);
		data->player.plane_y = old_plane_x * sin(rot_speed) + data->player.plane_y * cos(rot_speed);
	}
}

void    move_player(t_data *data)
{
	double  move_speed;
	double  next_x;
	double  next_y;

	move_speed = 3.0 * data->time.delta_time;
	
	if (data->player.key_up)
	{
		next_x = data->player.pos_x + data->player.dir_x * move_speed;
		next_y = data->player.pos_y + data->player.dir_y * move_speed;
		
		if (check_collision(data, next_x, data->player.pos_y))
		data->player.pos_x = next_x;
		if (check_collision(data, data->player.pos_x, next_y))
		data->player.pos_y = next_y;
	}
	if (data->player.key_down)
	{
		next_x = data->player.pos_x - data->player.dir_x * move_speed;
		next_y = data->player.pos_y - data->player.dir_y * move_speed;
		
		if (check_collision(data, next_x, data->player.pos_y))
			data->player.pos_x = next_x;
		if (check_collision(data, data->player.pos_x, next_y))
			data->player.pos_y = next_y;
	}
	if (data->player.key_left)
	{
		next_x = data->player.pos_x - data->player.plane_x * move_speed;
		next_y = data->player.pos_y - data->player.plane_y * move_speed;
		
		if (check_collision(data, next_x, data->player.pos_y))
			data->player.pos_x = next_x;
		if (check_collision(data, data->player.pos_x, next_y))
			data->player.pos_y = next_y;
	}
	if (data->player.key_right)
	{
		next_x = data->player.pos_x + data->player.plane_x * move_speed;
		next_y = data->player.pos_y + data->player.plane_y * move_speed;

		if (check_collision(data, next_x, data->player.pos_y))
			data->player.pos_x = next_x;
		if (check_collision(data, data->player.pos_x, next_y))
			data->player.pos_y = next_y;
	}
	directional_key(data);
}
