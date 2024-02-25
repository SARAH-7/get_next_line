/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:54:44 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/25 18:52:35 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	get_the_next_line(int bytes_read, char **line,
	char **buffer, char **remain)
{
	char	*temp;
	char	*temp1;

	temp1 = ft_strchr(*line, '\n');
	temp = NULL;
	while (bytes_read > 0 || *remain != NULL)
	{
		if (*remain)
		{
			*line = ft_strdup(*remain);
			free(*remain);
			*remain = NULL;
			if (bytes_read <= 0)
				break ;
		}
		if (*line == NULL)
			*line = ft_strdup(*buffer);
		else
		{
			temp = *line;
			*line = assign_line(temp, *buffer);
			free(temp);
			temp = NULL;
		}
		if (temp1)
		{
			*remain = ft_strdup(ft_remain_lines(*line, '\n'));
			temp = *line;
			*line = ft_strchr(temp, '\n');
			free(temp);
			temp = NULL;
			free(temp1);
			temp1 = NULL;
		}
		break ;
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*remain;
	char		*line;
	int			bytes_read;
	char		*temp;

	bytes_read = 0;
	buffer = NULL;
	line = NULL;
	temp = NULL;
	if (fd < 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + (size_t)1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp);
		free(buffer);
		free(remain);
		return (NULL);
	}
	while (bytes_read > 0 || remain != NULL)
	{
		buffer[bytes_read] = '\0';
		get_the_next_line(bytes_read, &line, &buffer, &remain);
		temp = ft_strchr(line, '\n');
		if (temp)
			break ;
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	free(buffer);
	buffer = NULL;
	return (line);
}
