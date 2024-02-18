/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:54:44 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/18 21:08:28 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*read_line;
	static char	*remain;
	char		*line;

	buffer = NULL;
	read_line = NULL;
	line = NULL;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while ((read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[BUFFER_SIZE] = '\0';
		if (remain)
		{
			read_line = ft_strdup(remain);
			free(remain);
		}
		if (!ft_strchr(buffer, '\n') && read_line == NULL)
			read_line = ft_strdup(buffer);
		else if (ft_strchr(buffer, '\n') && read_line == NULL)
			read_line = ft_strdup(buffer);
		else
			read_line = ft_strjoin(read_line, buffer);
		if (ft_strchr(buffer, '\n'))
		{
			remain = ft_strdup(ft_strchr(buffer, '\n') + 1);
			break ;
		}
		ft_bzero(buffer, BUFFER_SIZE + 1);
	}
	free(buffer);
	line = read_line;
	return (line);
}
