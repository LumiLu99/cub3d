/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching_implementation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:54:41 by yelu              #+#    #+#             */
/*   Updated: 2025/10/31 16:58:56 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// bool	touch(float px, float py, t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = px / TILE_SIZE;
// 	y = py / TILE_SIZE;
// 	if (data->map.map_arr[y][x] == '1')
// 		return (true);
// 	return (false);
// }

// int	distance(float x, float y)
// {
// 	return (sqrt(x * x + y * y));
// }

// float	fixed_dist(float x1, float y1, float x2, float y2, t_data *data)
// {
// 	float	delta_x;
// 	float	delta_y;
// 	float	angle;
// 	float	fix_dist;
	
// 	delta_x = x2 - x1;
// 	delta_y = y2 - y1;
// 	angle = atan2(delta_y, delta_x) - data->player.angle;
// 	fix_dist = distance(delta_x, delta_y) * cos(angle);
// 	return (fix_dist);
// }

// void	draw_line(t_data *data, float start_x, int i)
// {
// 	float	cos_angle;
// 	float	sin_angle;
// 	float	ray_x;
// 	float	ray_y;
// 	float	dist;
// 	float	height;
// 	int		start_y;
// 	int		end;

// 	cos_angle = cos(start_x);
// 	sin_angle = sin(start_x);
// 	ray_x = data->player.x;
// 	ray_y = data->player.y;
// 	while (!touch(ray_x, ray_y, data))
// 	{
// 		my_mlx_pixel_put(data, ray_x, ray_y, GREEN_PIXEL);
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}
// 	dist = fixed_dist(data->player.x, data->player.y, ray_x, ray_y, data);
// 	height = (TILE_SIZE / dist) * (WIDTH / 2);
// 	start_y = (HEIGHT - height) / 2;
// 	end = start_y + height;
// 	while (start_y < end)
// 	{
// 		my_mlx_pixel_put(data, i, start_y, 0x0000FF);
// 		start_y++;
// 	}
	
// }

// static void draw_ray(t_data *data)
// {
//     int i;
//     double ray_x;
//     double ray_y;
// 	int map_x;
// 	int map_y;
// 	double distance;
// 	int y;
// 	double fov_radians;
// 	double angle_step;

//     i = 0;
// 	fov_radians = FOV_DEGREE * (PI / 180);
//     while (1)
//     {
//         // Calculate the point on the ray at distance 'i'
//         ray_x = data->player.x + i * cos(data->player.angle);
//         ray_y = data->player.y + i * sin(data->player.angle);
// 		// Each time i increases, you are simply defining a new, larger triangle along the same line (the ray). 
// 		// The purpose of calculating the sides of this triangle is to find the exact (x, y) 
// 		// coordinates of the point at the end of that hypotenuse.
// 		my_mlx_pixel_put(data, ray_x, ray_y, GREEN_PIXEL);
// 		map_x = (int)ray_x / TILE_SIZE;
// 		map_y = (int)ray_y / TILE_SIZE;
// 		if (data->map.map_arr[map_y][map_x] == '1')
// 			break ;
// 		i++;
//     }
// 		//distance to wall
// 		distance = sqrt(pow(ray_x - data->player.x, 2) + pow(ray_y - data->player.y, 2));

// 		// Convert to wall height
// 		int wall_height = (int)((TILE_SIZE * 500) / distance);

// 		// Draw vertical wall slice in the middle
// 		int line_x = WIDTH / 2;
// 		int line_start = (HEIGHT / 2) - (wall_height / 2);
// 		int line_end = (HEIGHT / 2) + (wall_height / 2);

// 		y = line_start;
// 		while (y < line_end)
// 		{
// 			my_mlx_pixel_put(data, line_x, y, WHITE_PIXEL);
// 			y++;
// 		}
// }

int	update(void *param)
{
	t_data	*data;
	// float	fraction;
	// float	start_x;
	// int		i;
	
	data = (t_data *)param;
	move_player(data);
	ft_bzero(data->img.addr, WIDTH * HEIGHT * (data->img.bits_per_pixel / 8));
	print_minimap(data);
	print_player_pixel(data);
	// fraction = PI / 3 / WIDTH;
	// // fraction = PI / 3 / WIDTH;: You define a Field of View of 60 degrees (PI / 3 radians). 
	// // This line calculates the tiny angle difference between each of the rays you will cast.
	// start_x = data->player.angle - PI / 6;
	// // calculate the angle for the very first ray, which is on the far-left side of your FOV (player's angle minus 30 degrees).
	// i = 0;
	// while (i < WIDTH)
	// {
	// 	draw_line(data, start_x, i);
	// 	start_x += fraction;
	// 	i++;
	// }
	// draw_ray(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;

	(void)argv;
	if (argc == 2)
	{
		init_data(&data);
		mlx_hook(data.win, KeyPress, KeyPressMask, on_keypress, &data);
		mlx_hook(data.win, KeyRelease, KeyReleaseMask, on_keyrelease, &data);
		mlx_loop_hook(data.mlx, update, &data);
		mlx_hook(data.win, DestroyNotify, SubstructureNotifyMask,
			ft_close, &data);
		mlx_loop(data.mlx);
	}
	else
		print_error_exit("Usage: ./cub3D <map file.ber>\n");
}

void	init_player(t_player *player)
{
	player->x = 70;
	player->y = 70;
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
	float	rotation_speed;
	// float	cos_angle;
	// float	sin_angle;
	float	next_x;
	float	next_y;

	move_speed = 2;
	rotation_speed = 0.03;
	if (data->player.left_rotate)
	{
    	data->player.angle -= rotation_speed;
	}
    if (data->player.right_rotate)
	{
    	data->player.angle += rotation_speed;	
	}
	if (data->player.angle < 0)
	{
    	data->player.angle += 2 * PI;
	}
    if (data->player.angle > 2 * PI)
	{
    	data->player.angle -= 2 * PI;
	}
	if (data->player.key_up)
    {
		next_x = data->player.x + cos(data->player.angle) * move_speed;
		next_y = data->player.y + sin(data->player.angle) * move_speed;

		if (data->map.map_arr[(int)(data->player.y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] != '1')
			data->player.x = next_x;
		if (data->map.map_arr[(int)(next_y / TILE_SIZE)][(int)(data->player.x / TILE_SIZE)] != '1')
			data->player.y = next_y;
        // data->player.x += cos(data->player.angle) * move_speed; //delta-x, change of X in one step
        // data->player.y += sin(data->player.angle) * move_speed; //delta-y, change of y in one step
    }
    if (data->player.key_down)
    {
		next_x = data->player.x - cos(data->player.angle) * move_speed;
		next_y = data->player.y - sin(data->player.angle) * move_speed;
	
		if (data->map.map_arr[(int)(data->player.y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] != '1')
			data->player.x = next_x;
		if (data->map.map_arr[(int)(next_y / TILE_SIZE)][(int)(data->player.x / TILE_SIZE)] != '1')
			data->player.y = next_y;
        // data->player.x -= cos(data->player.angle) * move_speed;
        // data->player.y -= sin(data->player.angle) * move_speed;
    }
	if (data->player.key_left)
	{
		next_x = data->player.x + sin(data->player.angle) * move_speed;
		next_y = data->player.y - cos(data->player.angle) * move_speed;
		if (data->map.map_arr[(int)(data->player.y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] != '1')
			data->player.x = next_x;
		if (data->map.map_arr[(int)(next_y / TILE_SIZE)][(int)(data->player.x / TILE_SIZE)] != '1')
			data->player.y = next_y;
		// data->player.x += sin(data->player.angle) * move_speed;
		// data->player.y -= cos(data->player.angle) * move_speed;
	}
	if (data->player.key_right)
	{
		next_x = data->player.x - sin(data->player.angle) * move_speed;
		next_y = data->player.y + cos(data->player.angle) * move_speed;
		if (data->map.map_arr[(int)(data->player.y / TILE_SIZE)][(int)(next_x / TILE_SIZE)] != '1')
			data->player.x = next_x;
		if (data->map.map_arr[(int)(next_y / TILE_SIZE)][(int)(data->player.x / TILE_SIZE)] != '1')
			data->player.y = next_y;
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
