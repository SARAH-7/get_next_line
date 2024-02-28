/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:55:26 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/28 18:22:10 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char		*str;
	size_t		len_s1;
	size_t		len_s2;

	len_s1 = 0;
	len_s2 = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[len_s1])
		len_s1++;
	while (s2[len_s2])
		len_s2++;
	str = (char *)malloc(len_s1 + len_s2 + 1);
	if (!str)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (str - (len_s1 + len_s2));
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*result;
	size_t	len;

	len = 0;
	while (s1[len])
		len++;
	if (!s1)
		return (NULL);
	str = malloc ((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	result = str;
	while (*s1)
		*str++ = *s1++;
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
		t = (char *)malloc((s - p) + 2);
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
