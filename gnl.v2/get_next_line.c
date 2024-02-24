/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:54:44 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/24 19:55:37 by sbakhit          ###   ########.fr       */
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

void	begining_of_line(char **line, char **buffer, char **remain)
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
}

void	get_the_next_line(char **line, char **buffer, char **remain)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	temp1 = ft_strchr(*line, '\n');
	temp = ft_strchr(*buffer, '\n');
	if (temp1 && *line)
	{
		*remain = ft_strdup(ft_remain_lines(*line, '\n'));
		free(*line);
		*line = temp1;
	}
	else if (temp)
	{
		*remain = ft_strdup(ft_remain_lines(*buffer, '\n'));
		temp2 = *line;
		*line = ft_strjoin(temp2, temp);
		free(temp2);
		free(temp1);
	}
	else if (!temp1 && *line)
	{
		temp2 = *line;
		if ((**line == **buffer) && (ft_strlen(*line) == ft_strlen(*buffer)))
			return ;
		*line = assign_line(temp2, *buffer);
		free(temp2);
	}
	if (temp)
		free(temp);
}

void	check_remain(char **line, char **buffer, char **remain)
{
	char	*temp2;

	temp2 = ft_strdup(*remain);
	free(*remain);
	*remain = NULL;
	*line = assign_line(temp2, *buffer);
	free(temp2);
}

void	if_conditions(int bytes_read, char **line,
	char **buffer, char **remain)
{
	while (bytes_read > 0 || remain != NULL)
	{
		if (*remain != NULL)
			check_remain(line, buffer, remain);
		if (bytes_read <= 0 && *line == NULL)
			break ;
		begining_of_line(line, buffer, remain);
		if (*remain)
			break ;
		get_the_next_line(line, buffer, remain);
		break ;
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*remain;
	char		*line;
	int			bytes_read;
	char		*temp2;

	bytes_read = 0;
	buffer = NULL;
	line = NULL;
	temp2 = NULL;
	if (fd < 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + (size_t)1);
	if (!buffer)
		return (NULL);

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp2);
		free(buffer);
		free(remain);
		return (NULL);
	}
	while (bytes_read > 0 || remain != NULL)
	{
		buffer[bytes_read] = '\0';
		if_conditions(bytes_read, &line, &buffer, &remain);
		temp2 = ft_strchr(line, '\n');
		if (temp2)
			break ;
		ft_bzero(buffer, BUFFER_SIZE + (size_t)1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (temp2)
		free(temp2);
	free(buffer);
	return (line);
}
