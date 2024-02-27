/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:54:44 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/27 20:04:12 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_variable(char **variable)
{
	free(*variable);
	*variable = NULL;
}

void	remain_check(char **remain, char **line)
{
	if (*remain)
	{
		*line = ft_strdup(*remain);
		free_variable(remain);
	}
}

void	line_check(char **line, char **buffer, char *temp)
{
	if (*line == NULL)
		*line = ft_strdup(*buffer);
	else
	{
		temp = *line;
		*line = assign_line(temp, *buffer);
		free_variable(&temp);
	}
}

void	get_the_next_line(int bytes_read, char **line,
	char **buffer, char **remain)
{
	char	*temp;
	char	*temp1;

	temp = NULL;
	temp1 = NULL;
	while (bytes_read > 0 || *remain != NULL)
	{
		remain_check(remain, line);
		if (bytes_read <= 0 && *line == NULL)
			break ;
		line_check(line, buffer, temp);
		temp1 = ft_strchr(*line, '\n');
		if (temp1)
		{
			*remain = ft_strdup(ft_remain_lines(*line, '\n'));
			temp = *line;
			*line = ft_strchr(temp, '\n');
			free_variable(&temp);
			free_variable(&temp1);
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
	if (fd < 0 || (BUFFER_SIZE >= INT_MAX))
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return (free_variable(&remain), NULL);
	}
	while (bytes_read > 0 || remain != NULL)
	{
		buffer[bytes_read] = '\0';
		get_the_next_line(bytes_read, &line, &buffer, &remain);
		temp = ft_strchr(line, '\n');
		if (temp)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (temp)
		free_variable(&temp);
	if (line && line[0] == '\0')
		free_variable(&line);
	return (free_variable(&buffer), line);
}
