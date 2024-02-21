/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:21:13 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/21 20:41:45 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" 

int	main(void)
{
	int		fd;
	char	*line = NULL;
	int		count;

	count = 0;
	fd = open("ex.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		printf("[%d] %s", count, line);
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}
