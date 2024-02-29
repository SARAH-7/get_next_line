/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:55:26 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/29 15:46:58 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" 

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*result;

	if (!s1)
		return (NULL);
	str = malloc ((ft_strlen(s1) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	result = str;
	while (*s1)
		*str++ = *s1++;
	*str = '\0';
	return (result);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char		*str;
	char		*result;

	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	result = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s++ == (unsigned char)c)
		return (((char *)s));
	if ((unsigned char)c == 0 && *s == 0)
		return ((char *)s);
	return (NULL);
}

char	*ft_get_line(const char *s, int c)
{
	char	*p;
	char	*t;
	int		j;

	t = NULL;
	j = 0;
	if (!s)
		return (NULL);
	p = (char *)s;
	while (*s && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
	{
		t = malloc((s - p) + 2);
		if (!t)
			return (NULL);
		while (j <= s - p)
		{
			t[j] = p[j];
			j++;
		}
		t[j] = '\0';
		return (t);
	}
	return (NULL);
}
