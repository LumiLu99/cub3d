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

static void	rotate_player(t_data *data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(rot_speed)
		- data->player.dir_y * sin(rot_speed);
	data->player.dir_y = old_dir_x * sin(rot_speed)
		+ data->player.dir_y * cos(rot_speed);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(rot_speed)
		- data->player.plane_y * sin(rot_speed);
	data->player.plane_y = old_plane_x * sin(rot_speed)
		+ data->player.plane_y * cos(rot_speed);
}

static void	attempt_move(t_data *data, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + move_x;
	new_y = data->player.pos_y + move_y;
	if (check_collision(data, new_x, data->player.pos_y))
		data->player.pos_x = new_x;
	if (check_collision(data, data->player.pos_x, new_y))
		data->player.pos_y = new_y;
}

void	move_player(t_data *data)
{
	double	s;

	s = 3.0 * data->time.delta_time;
	if (data->player.left_rotate)
		rotate_player(data, -0.03);
	if (data->player.right_rotate)
		rotate_player(data, 0.03);
	if (data->player.key_up)
		attempt_move(data, data->player.dir_x * s, data->player.dir_y * s);
	if (data->player.key_down)
		attempt_move(data, -data->player.dir_x * s, -data->player.dir_y * s);
	if (data->player.key_left)
		attempt_move(data, -data->player.plane_x * s,
			-data->player.plane_y * s);
	if (data->player.key_right)
		attempt_move(data, data->player.plane_x * s, data->player.plane_y * s);
}
