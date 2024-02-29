/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:54:44 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/29 14:30:47 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_variable(char **variable)
{
	free(*variable);
	*variable = NULL;
}

void	line_append(char **line, char **buffer, char *temp)
{
	if (*line == NULL)
		*line = ft_strdup(*buffer);
	else
	{
		temp = *line;
		*line = ft_strjoin(temp, *buffer);
		free_variable(&temp);
	}
}

void	get_the_next_line(int bytes_read, char **line,
	char **buffer, char **remain)
{
	char	*temp;

	temp = NULL;
	if (*remain)
	{
		*line = ft_strdup(*remain);
		free_variable(remain);
	}
	if (bytes_read > 0 || *line)
	{
		line_append(line, buffer, temp);
		if (ft_strchr(*line, '\n'))
		{
			*remain = ft_strdup(ft_strchr(*line, '\n'));
			temp = *line;
			*line = ft_get_line(*line, '\n');
			free_variable(&temp);
		}
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*remain[OPEN_MAX];
	char		*line;
	int			bytes_read;

	line = NULL;
	if (fd < 0 || (BUFFER_SIZE >= INT_MAX))
		return (NULL);
	buffer = malloc((size_t)(BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (free_variable(&buffer), free_variable(&remain[fd]), NULL);
	while (bytes_read > 0 || remain[fd])
	{
		buffer[bytes_read] = '\0';
		get_the_next_line(bytes_read, &line, &buffer, &remain[fd]);
		if (ft_strchr(line, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (line && line[0] == '\0')
		free_variable(&line);
	return (free_variable(&buffer), line);
}
