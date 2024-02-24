/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:54:44 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/24 21:10:47 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		buffer[BUFFER_SIZE] = '\0';
		if (remain)
		{
			line = ft_strdup(remain);
			free(remain);
			remain = NULL;
			if (bytes_read <= 0)
				break ;
		}
		if (line == NULL)
			line = ft_strdup(buffer);
		else
			line = assign_line(line, buffer);
		if (ft_strchr(line, '\n'))
		{
			remain = ft_strdup(ft_remain_lines(line, '\n'));
			line = ft_strchr(line, '\n');
			break ;
		}
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (line);
}
// char	*get_next_line(int fd)
// {
// 	char		*buffer;
// 	char		*read_line;
// 	static char	*remain;
// 	char		*line;
// 	int			bytes_read;

// 	bytes_read = 0;
// 	buffer = NULL;
// 	read_line = NULL;
// 	line = NULL;
// 	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
// 	if (!buffer)
// 		return (NULL);
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	while (bytes_read > 0 || remain != NULL)
// 	{
// 		if (remain)
// 		{
// 			read_line = ft_strdup(remain);
// 			free(remain);
// 			remain = NULL;
// 			if (bytes_read <= 0)
// 				break ;
// 		}
// 		buffer[BUFFER_SIZE] = '\0';
// 		if (!ft_strchr(buffer, '\n') && read_line == NULL)
// 			read_line = ft_strdup(buffer);
// 		else if (ft_strchr(buffer, '\n') && read_line == NULL)
// 			read_line = ft_strdup(ft_strchr(buffer, '\n'));
// 		else if (ft_strchr(buffer, '\n') && read_line != NULL)
// 			read_line = ft_strjoin(read_line, ft_strchr(buffer, '\n'));
// 		else
// 			read_line = ft_strjoin(read_line, buffer);
// 		if (ft_strchr(buffer, '\n'))
// 		{
// 			remain = ft_strdup(ft_remain_lines(buffer, '\n'));
// 			break ;
// 		}
// 		ft_bzero(buffer, BUFFER_SIZE + 1);
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	}
// 	free(buffer);
// 	line = read_line;
// 	return (line);
// }
