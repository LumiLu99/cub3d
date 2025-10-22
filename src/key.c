/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:04:19 by yelu              #+#    #+#             */
/*   Updated: 2025/10/21 17:47:43 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	on_keypress(int keysym, t_data *data)
{
	if (keysym == XK_w)
		data->player.key_up = true;
	else if (keysym == XK_a)
		data->player.key_left = true;
	else if (keysym == XK_s)
		data->player.key_down = true;
	else if (keysym == XK_d)
		data->player.key_right = true;
	else if (keysym == XK_Left)
		data->player.left_rotate = true;
	else if (keysym == XK_Right)
		data->player.right_rotate = true;
	return (0);
}

int	on_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_close(data);
	else if (keysym == XK_w)
		data->player.key_up = false;
	else if (keysym == XK_s)
		data->player.key_down = false;
	else if (keysym == XK_a)
		data->player.key_left = false;
	else if (keysym == XK_d)
		data->player.key_right = false;
	else if (keysym == XK_Left)
		data->player.left_rotate = false;
	else if (keysym == XK_Right)
		data->player.right_rotate = false;
	return (0);
}
