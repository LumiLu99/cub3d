/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:56:07 by yelu              #+#    #+#             */
/*   Updated: 2025/10/15 19:31:15 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>

// Colours
#define RED_PIXEL 0xFF0000

// Window
# define WIDTH 1024
# define HEIGHT 768

// Textures
# define TEX_SIZE 50

typedef struct s_player
{
	int	x;
	int	y;
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
	char	map[6][6];
}	t_data;


int	ft_close(t_data *data);
int	on_keypress(int keysym, t_data *data);

//utils
void	print_error_exit(char *str);

#endif