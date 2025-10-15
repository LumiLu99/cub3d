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

#define RED_PIXEL 0xFF0000

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_player	player;
	char	map[6][6];
}	t_data;


int	ft_close(t_data *data);
int	on_keypress(int keysym, t_data *data);

#endif