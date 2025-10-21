/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:54:53 by yelu              #+#    #+#             */
/*   Updated: 2025/10/21 12:06:31 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->x = 20;
	player->y = 20;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
}


