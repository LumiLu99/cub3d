/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:26:12 by yelu              #+#    #+#             */
/*   Updated: 2026/01/02 22:58:20 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_rays_minimap(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		process_minimap_ray(data, x);
		x++;
	}
}
