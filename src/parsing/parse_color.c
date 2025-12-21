/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:25:06 by wshee             #+#    #+#             */
/*   Updated: 2025/12/21 19:29:02 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

static int	convert_rgb_to_int(const char *str)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			sum = (sum * 10) + (str[i] - 48);
			i++;
		}
		else
		{
			return -1;
		}
	}
	return (sum);
}

void free_2d_array(void **array)
{
	int i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
}

int parse_color(char *identifier, char *color)
{
	char **rgb = ft_split(color, ',');
	int counter = 0;
	while (rgb[counter])
		counter++;
	if (counter != 3)
		return (-1);
	int r = convert_rgb_to_int(rgb[0]);
	int g = convert_rgb_to_int(rgb[1]);
	int b = convert_rgb_to_int(rgb[2]);
	// convert into hexa format 0xFFFFFF in integer form
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r << 16 | g << 8 | b);
}
