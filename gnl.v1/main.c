/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:21:13 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/25 17:50:22 by sbakhit          ###   ########.fr       */
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
	if (fd == -1)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		printf("[%d]%s", count, line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}
