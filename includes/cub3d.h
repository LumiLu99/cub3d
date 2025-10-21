/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:56:07 by yelu              #+#    #+#             */
/*   Updated: 2025/10/21 12:22:06 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

// Colours
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define WHITE_PIXEL 0xFFFFFF
# define BLUE_PIXEL 0x0000FF
# define GRAY_PIXEL 0x808080

// Window
# define WIDTH 1920
# define HEIGHT 1080

// Textures
# define TEX_SIZE 50

// Tile size
# define TILE_SIZE 20

// Maths
# define PI 3.14159265359

typedef struct s_map
{
	char	*map_arr[8];
	int		x_len_map;
	int		y_len_map;

}	t_map;

typedef struct s_minimap
{
	int	mp_x;
	int	mp_y;
}	t_minimap;

typedef struct s_player
{
	int	x;
	int	y;
	bool	key_up;
	bool	key_down;
	bool	key_right;
	bool	key_left;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		endian;
	int		bits_per_pixel;
	int		line_len;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_player	player;
	t_img		img;
	t_map		map;
	t_minimap	mini;
}	t_data;


int	ft_close(t_data *data);
int	update(void *param);

// key
int	on_keypress(int keysym, t_data *data);
int	on_keyrelease(int keysym, t_data *data);

// init
void	init_mlx(t_data *data);
void	init_player(t_player *player);

// utils
void	print_error_exit(char *str);

#endif