/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:28:09 by wshee             #+#    #+#             */
/*   Updated: 2025/11/27 21:42:40 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"
# include <stdio.h>

bool check_file_ext(const char *filename)
{
	const char *ext = ".cub";
	size_t filename_len = ft_strlen(filename);
	size_t ext_len = ft_strlen(ext);

	if (filename[0] == '\0')
		return false;
	if (filename_len == ext_len)
		return false;
	while (filename[filename_len - 1] && ext_len > 0)
	{
		if (filename[filename_len - 1] != ext[ext_len - 1])
			return false;
		filename_len--;
		ext_len--;
	}
	return true;
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Number of arguments must be 2");
		return 1;
	}
	if(!check_file_ext(av[1]))
	{
		printf("Invalid map");
		return 1;
	}
	return 0;
}
