/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:55:26 by yelu              #+#    #+#             */
/*   Updated: 2025/10/04 15:03:16 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main()
{
	t_data	data;

    data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600, "Cub3D");
	if (!data.win_ptr)
		return (1);
    mlx_loop(data.mlx_ptr);
    return 0;
}
