/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:54:53 by yelu              #+#    #+#             */
/*   Updated: 2025/11/11 19:36:25 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    move_player(t_data *data)
{
    double  move_speed;
    double  next_x;
    double  next_y;
    double  rot_speed;

    move_speed = 0.03;
    rot_speed = 0.03;
    if (data->player.key_up)
    {
        next_x = data->player.pos_x + data->player.dir_x * move_speed;
        next_y = data->player.pos_y + data->player.dir_y * move_speed;

        if (data->map.map_arr[(int)data->player.pos_y][(int)next_x] != '1') 
            data->player.pos_x = next_x;
        if (data->map.map_arr[(int)next_y][(int)data->player.pos_x] != '1')
            data->player.pos_y = next_y;
    }
    if (data->player.key_down)
    {
        // 3. Use move_speed, NOT move_speed * delta_time
        next_x = data->player.pos_x - data->player.dir_x * move_speed;
        next_y = data->player.pos_y - data->player.dir_y * move_speed;
        if (data->map.map_arr[(int)(data->player.pos_y)][(int)(next_x)] != '1')
            data->player.pos_x = next_x;
        if (data->map.map_arr[(int)(next_y)][(int)(data->player.pos_x)] != '1')
            data->player.pos_y = next_y;
    }
    if (data->player.key_left)
    {
        next_x = data->player.pos_x - data->player.plane_x * move_speed;
        next_y = data->player.pos_y - data->player.plane_y * move_speed;
        if (data->map.map_arr[(int)(data->player.pos_y)][(int)(next_x)] != '1')
            data->player.pos_x = next_x;
        if (data->map.map_arr[(int)(next_y)][(int)(data->player.pos_x)] != '1')
            data->player.pos_y = next_y;
    }
    if (data->player.key_right)
    {
        next_x = data->player.pos_x + data->player.plane_x * move_speed;
        next_y = data->player.pos_y + data->player.plane_y * move_speed;
        if (data->map.map_arr[(int)(data->player.pos_y)][(int)(next_x)] != '1')
            data->player.pos_x = next_x;
        if (data->map.map_arr[(int)(next_y)][(int)(data->player.pos_x)] != '1')
            data->player.pos_y = next_y;
    }
    if (data->player.left_rotate)
    {
        double old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(rot_speed) - data->player.dir_y * sin(rot_speed);
        data->player.dir_y = old_dir_x * sin(rot_speed) + data->player.dir_y * cos(rot_speed);
        double old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(rot_speed) - data->player.plane_y * sin(rot_speed);
        data->player.plane_y = old_plane_x * sin(rot_speed) + data->player.plane_y * cos(rot_speed);
    }
    if (data->player.right_rotate)
    {
        double old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(-rot_speed) - data->player.dir_y * sin(-rot_speed);
        data->player.dir_y = old_dir_x * sin(-rot_speed) + data->player.dir_y * cos(-rot_speed);
        double old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(-rot_speed) - data->player.plane_y * sin(-rot_speed);
        data->player.plane_y = old_plane_x * sin(-rot_speed) + data->player.plane_y * cos(-rot_speed);
    }
}
