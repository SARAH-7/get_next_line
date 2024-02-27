/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:21:13 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/27 18:03:36 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" 

int	main(void)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open("hi.txt", O_RDONLY);
	line = "hisham";
	while (line != NULL)
	{
		count++;
		line = get_next_line(fd);
		printf("[%d](%s)", count, line);
		free(line);
	}
	close(fd);
	return (0);
}
