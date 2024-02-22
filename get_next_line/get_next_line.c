/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:54:44 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/22 21:57:56 by sbakhit          ###   ########.fr       */
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

char	*begining_of_line(char **line, char **buffer, char **remain)
{
	char	*temp;

	temp = ft_strchr(*buffer, '\n');
	if (!temp && *line == NULL)
		*line = ft_strdup(*buffer);
	else if (temp && *line == NULL)
	{
		if (ft_remain_lines(*buffer, '\n') != NULL
			&& ft_strncmp(ft_remain_lines(*buffer, '\n'), "", 1) != 0)
			*remain = ft_strdup(ft_remain_lines(*buffer, '\n'));
		*line = ft_strdup(temp);
		free(temp);
	}
	return (*line);
}

char	*get_the_next_line(char **line, char **buffer, char **remain)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	temp1 = ft_strchr(*line, '\n');
	temp = ft_strchr(*buffer, '\n');
	if (temp1 && *line)
	{
		*remain = ft_strdup(ft_remain_lines(*line, '\n'));
		*line = temp1;
	}
	else if (temp)
	{
		*remain = ft_strdup(ft_remain_lines(*buffer, '\n'));
		*line = ft_strjoin(*line, temp);
		free(temp);
	}
	else if (!temp1 && *line)
	{
		temp2 = *line;
		*line = assign_line(temp2, *buffer);
		free(temp2);
	}
	return (*line);
}

char	*check_remain(char **line, char **buffer, char **remain)
{
	char	*temp2;

	temp2 = ft_strdup(*remain);
	*line = assign_line(temp2, *buffer);
	free(*remain);
	*remain = NULL;
	free(temp2);
	return (*line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*remain;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	bytes_read = 0;
	buffer = NULL;
	line = NULL;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0 || remain != NULL)
	{
		buffer[bytes_read] = '\0';
		if (remain != NULL)
			line = check_remain(&line, &buffer, &remain);
		if (bytes_read <= 0 && line == NULL)
			break ;
		line = begining_of_line(&line, &buffer, &remain);
		if (remain)
			break ;
		line = get_the_next_line(&line, &buffer, &remain);
		break ;
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (line);
}
