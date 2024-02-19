/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:54:44 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/19 17:41:24 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*read_line;
	static char	*remain;
	char		*line;
	int			bytes_read;

	bytes_read = 0;
	buffer = NULL;
	read_line = NULL;
	line = NULL;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0 || remain != NULL)
	{
		if (remain)
		{
			read_line = ft_strdup(remain);
			read_line = ft_strjoin(read_line, buffer);
			free(remain);
			remain = NULL;
			if (bytes_read <= 0)
				break ;
		}
		buffer[BUFFER_SIZE] = '\0';
		if (!ft_strchr(buffer, '\n') && read_line == NULL)
			read_line = ft_strdup(buffer);
		else
		{
			if (read_line == NULL)
			{
				remain = ft_strdup(ft_remain_lines(buffer, '\n'));
				read_line = ft_strdup(ft_strchr(buffer, '\n'));
			}
			else
			{
				remain = ft_strdup(ft_remain_lines(read_line, '\n'));
				read_line = ft_strchr(read_line, '\n');
			}
			break ;
		}
		if (bytes_read <= 0 && read_line == NULL)
			read_line = ft_strdup(buffer);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	line = read_line;
	return (line);
}
