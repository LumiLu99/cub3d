/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:54:53 by yelu              #+#    #+#             */
/*   Updated: 2025/11/10 18:22:34 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->pos_x = 5.5;
	player->pos_y = 5.5;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->angle = PI / 2; // player facing down

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	move_player(t_data *data)
{
	int	move_speed;
	// float	rotation_speed;
	// float	cos_angle;
	// float	sin_angle;
	double	next_x;
	double	next_y;

	move_speed = data->time.delta_time * 5.0;
	// rotation_speed = data->time.delta_time * 3.0;
	// if (data->player.left_rotate)
	// {
    // 	data->player.angle -= rotation_speed;
	// }
    // if (data->player.right_rotate)
	// {
    // 	data->player.angle += rotation_speed;	
	// }
	// if (data->player.angle < 0)
	// {
    // 	data->player.angle += 2 * PI;
	// }
    // if (data->player.angle > 2 * PI)
	// {
    // 	data->player.angle -= 2 * PI;
	// }
	if (data->player.key_up)
    {
		next_x = data->player.pos_x + data->player.dir_x * move_speed * data->time.delta_time;
		next_y = data->player.pos_y + data->player.dir_y * move_speed * data->time.delta_time;

		if (data->map.map_arr[(int)(data->player.pos_y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] != '1')
			data->player.pos_x = next_x;
		if (data->map.map_arr[(int)(next_y / TILE_SIZE)][(int)(data->player.pos_x / TILE_SIZE)] != '1')
			data->player.pos_y = next_y;
        // data->player.x += cos(data->player.angle) * move_speed; //delta-x, change of X in one step
        // data->player.y += sin(data->player.angle) * move_speed; //delta-y, change of y in one step
    }
    if (data->player.key_down)
    {
		next_x = data->player.pos_x - data->player.dir_x * move_speed * data->time.delta_time;
 		next_y = data->player.pos_y - data->player.dir_y * move_speed * data->time.delta_time;
	
		if (data->map.map_arr[(int)(data->player.pos_y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] != '1')
			data->player.pos_x = next_x;
		if (data->map.map_arr[(int)(next_y / TILE_SIZE)][(int)(data->player.pos_x / TILE_SIZE)] != '1')
			data->player.pos_y = next_y;
        // data->player.x -= cos(data->player.angle) * move_speed;
        // data->player.y -= sin(data->player.angle) * move_speed;
    }
	if (data->player.key_left)
	{
		next_x = data->player.pos_x - data->player.plane_x * move_speed * data->time.delta_time;
		next_y = data->player.pos_y - data->player.plane_y * move_speed * data->time.delta_time;
		if (data->map.map_arr[(int)(data->player.pos_y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] != '1')
			data->player.pos_x = next_x;
		if (data->map.map_arr[(int)(next_y / TILE_SIZE)][(int)(data->player.pos_x / TILE_SIZE)] != '1')
			data->player.pos_y = next_y;
		// data->player.x += sin(data->player.angle) * move_speed;
		// data->player.y -= cos(data->player.angle) * move_speed;
	}
	if (data->player.key_right)
	{
		next_x = data->player.pos_x + data->player.plane_x * move_speed * data->time.delta_time;
		next_y = data->player.pos_y + data->player.plane_y * move_speed * data->time.delta_time;
		if (data->map.map_arr[(int)(data->player.pos_y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] != '1')
			data->player.pos_x = next_x;
		if (data->map.map_arr[(int)(next_y / TILE_SIZE)][(int)(data->player.pos_x / TILE_SIZE)] != '1')
			data->player.pos_y = next_y;
		// data->player.x -= sin(data->player.angle) * move_speed;
		// data->player.y += cos(data->player.angle) * move_speed;
	}
    // Note: A/D keys should be for "strafing" (moving left/right sideways)
    // You can add this later using angles perpendicular to the player's view.
	// cos_angle = cos(data->player.angle);
	// sin_angle = sin(data->player.angle);
	// if (data->player.left_rotate)
	// 	data->player.angle -= angle_speed;
	// if (data->player.right_rotate)
	// 	data->player.angle += angle_speed;
	// if (data->player.angle > 2 * PI)
	// 	data->player.angle = 0;
	// if (data->player.angle < 0)
	// 	data->player.angle = 2 * PI;
	// if (data->player.key_up)
	// {
	// 	data->player.x += cos_angle * speed;
	// 	data->player.y += sin_angle * speed;
	// }
	// if (data->player.key_down)
	// {
	// 	data->player.x -= cos_angle * speed;
	// 	data->player.y -= sin_angle * speed;
	// }
	// if (data->player.key_left)
	// {
	// 	data->player.x += sin_angle * speed;
	// 	data->player.y -= cos_angle * speed;
	// }
	// if (data->player.key_right)
	// {
	// 	data->player.x -= sin_angle * speed;
	// 	data->player.y += cos_angle * speed;
	// }
}
