/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:25:06 by wshee             #+#    #+#             */
/*   Updated: 2026/01/01 15:18:36 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	convert_rgb_to_int(const char *str);
int	parse_color(char *identifier, char *color);

static int	convert_rgb_to_int(const char *str)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		sum = (sum * 10) + (str[i] - 48);
		i++;
	}
	return (sum);
}

// ensure that there are 3 elements passed in as color
// return type: convert into hexa format 0xFFFFFF in integer form
int	parse_color(char *identifier, char *color)
{
	char	**rgb;
	int		counter;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(color, ',');
	counter = 0;
	while (rgb[counter])
		counter++;
	if (counter != 3)
	{
		free_2d_array(rgb);
		return (-1);
	}
	r = convert_rgb_to_int(rgb[0]);
	g = convert_rgb_to_int(rgb[1]);
	b = convert_rgb_to_int(rgb[2]);
	free_2d_array(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}
