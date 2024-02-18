/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:54:44 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/18 16:10:15 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	char		*read_line;
	static char	*remain;

	line = NULL;
	buffer = NULL;
	read_line = NULL;
	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!buffer)
		return (NULL);
	while (read(fd, buffer, BUFFER_SIZE))
	{
		if (remain)
			read_line = ft_strdup(remain);
		if (!ft_strchr(buffer, '\n') && read_line == NULL)
			read_line = ft_strdup(buffer);
		else if (!ft_strchr(buffer, '\n') && read_line != NULL)
			read_line = ft_strjoin(read_line, buffer);
		if (ft_strchr(buffer, '\n'))
		{
			// printf("buffer is %s\n", buffer);
			// char *p = ft_strchr(buffer, '\n');
			// printf("p is %s\n", p);
			read_line = ft_strjoin(read_line, buffer);
			// printf("read_line %s\n", read_line);
			remain = ft_remain_lines(buffer, '\n');
			// printf("remain: %s\n", remain);
			break ;
		}
	}
	line = read_line;
	return (line);
}

// char	*get_next_line(int fd)
// {
// 	char		*buffer;
// 	char		*line;
// 	char		*read_line;
// 	static char	*remain;

// 	line = NULL;
// 	buffer = NULL;
// 	read_line = NULL;
// 	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
// 	if (!buffer)
// 		return (NULL);
// 	while (read(fd, buffer, BUFFER_SIZE))
// 	{
// 		if (remain)
// 			read_line = ft_strdup(remain);
// 		if (!ft_strchr(buffer, '\n') && read_line == NULL)
// 			read_line = ft_strdup(buffer);
// 		else if (!ft_strchr(buffer, '\n') && read_line != NULL)
// 			read_line = ft_strjoin(read_line, buffer);
// 		if (ft_strchr(buffer, '\n'))
// 		{
// 			printf("buffer is %s\n", buffer);
// 			read_line = ft_strjoin(read_line, buffer);
// 			remain = ft_remain_lines(buffer + 1, '\n');
// 			break ;
// 		}
// 	}
// 	line = read_line;
// 	return (line);
// }
