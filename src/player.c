/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:54:53 by yelu              #+#    #+#             */
/*   Updated: 2025/10/21 19:33:44 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->x = 50;
	player->y = 50;
	player->angle = PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	move_player(t_data *data)
{
	int	speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = 3;
	angle_speed = 0.03;
	cos_angle = cos(data->player.angle);
	sin_angle = sin(data->player.angle);
	if (data->player.left_rotate)
		data->player.angle -= angle_speed;
	if (data->player.right_rotate)
		data->player.angle += angle_speed;
	if (data->player.angle > 2 * PI)
		data->player.angle = 0;
	if (data->player.angle < 0)
		data->player.angle = 2 * PI;
	if (data->player.key_up)
	{
		data->player.x += cos_angle * speed;
		data->player.y += sin_angle * speed;
	}
	if (data->player.key_down)
	{
		data->player.x -= cos_angle * speed;
		data->player.y -= sin_angle * speed;
	}
	if (data->player.key_left)
	{
		data->player.x += sin_angle * speed;
		data->player.y -= cos_angle * speed;
	}
	if (data->player.key_right)
	{
		data->player.x -= sin_angle * speed;
		data->player.y += cos_angle * speed;
	}
}
