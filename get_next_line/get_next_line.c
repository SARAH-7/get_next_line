/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:54:44 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/21 20:28:30 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- > 0 && (*s1 != '\0' || *s2 != '\0'))
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*remain;
	char		*line;
	int			bytes_read;

	bytes_read = 0;
	buffer = NULL;
	line = NULL;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0 || remain != NULL)
	{
		if (remain != NULL)
		{
			line = ft_strdup(remain);
			line = assign_line(line, buffer);
			free(remain);
			remain = NULL;
			if (bytes_read <= 0 && line == NULL)
				break ;
		}
		if (!ft_strchr(buffer, '\n') && line == NULL)
			line = ft_strdup(buffer);
		else if (ft_strchr(buffer, '\n') && line == NULL)
		{
			if (ft_remain_lines(buffer, '\n') != NULL && ft_strncmp(ft_remain_lines(buffer, '\n'), "", 1) != 0)
				remain = ft_strdup(ft_remain_lines(buffer, '\n'));
			line = ft_strdup(ft_strchr(buffer, '\n'));
			break ;
		}
		else if (ft_strchr(line, '\n') && line != NULL)
		{
			remain = ft_strdup(ft_remain_lines(line, '\n'));
			line = ft_strchr(line, '\n');
			break ;
		}
		else if (ft_strchr(buffer, '\n'))
		{
			if (ft_remain_lines(buffer, '\n') != NULL && ft_strncmp(ft_remain_lines(buffer, '\n'), "", 1) != 0)
				remain = ft_strdup(ft_remain_lines(buffer, '\n'));
			line = ft_strjoin(line, ft_strchr(buffer, '\n'));
			break ;
		}
		else if (!ft_strchr(line, '\n') && line != NULL)
			line = assign_line(line, buffer);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (line);
}
