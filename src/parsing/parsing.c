/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wshee <wshee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:28:09 by wshee             #+#    #+#             */
/*   Updated: 2025/11/26 21:05:17 by wshee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "stdbool.h"
# include "stdio.h"

bool check_file_ext(const char *filename)
{
	if (filename[0] == '\0')
		printf("Invalid map");
	if (*filename++)
		printf("%c", *filename);
	return true;
}

int main(int ac, char **av)
{
	if (ac != 2)
		printf("Number of arguments must be 2!");
	if(check_file_ext(av[1]))
		printf("Invalid map");
	return 0;
}
