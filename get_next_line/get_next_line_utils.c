/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbakhit <sbakhit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 13:55:26 by sbakhit           #+#    #+#             */
/*   Updated: 2024/02/22 19:52:20 by sbakhit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" 

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *)s + i) = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*r;

	if (size != 0 && count > UINT_MAX / size)
		return (NULL);
	r = malloc(count * size);
	if (r == NULL)
		return (NULL);
	ft_bzero(r, count * size);
	return (r);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*t;
	int		j;

	if (!s)
		return (NULL);
	t = NULL;
	i = 0;
	j = 0;
	while (*s)
	{
		if (*s == (unsigned char)c)
		{
			t = (char *)malloc(i + 2);
			if (t == NULL)
				return (NULL);
			s -= i;
			while (j <= i)
			{
				t[j] = s[j];
				j++;
			}
			t[j] = '\0';
			return (t);
		}
		s++;
		i++;
	}
	if ((unsigned char)c == 0 && *s == 0)
		return ((char *)(s - i));
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		a;
	int		b;

	a = 0;
	b = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *) malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, (ft_strlen(s1) + ft_strlen(s2)) + 1);
	while (s1[a] && s1[a] != '\0')
	{
		str[a] = s1[a];
		a++;
	}
	while (s2[b] && s2[b] != '\0')
	{
		str[a] = s2[b];
		if (s2[b] == '\n')
		{
			a++;
			break ;
		}
		a++;
		b++;
	}
	str[a] = '\0';
	return (str);
}

char	*assign_line(char const *s1, char const *s2)
{
	char	*str;
	int		a;
	int		b;

	a = 0;
	b = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *) malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (free((void *)s1), free((void *)s2), NULL);
	ft_bzero(str, (ft_strlen(s1) + ft_strlen(s2)) + 1);
	while (s1[a] && s1[a] != '\0')
	{
		str[a] = s1[a];
		a++;
	}
	while (s2[b] && s2[b] != '\0')
	{
		str[a] = s2[b];
		a++;
		b++;
	}
	str[a] = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*s;
	char	*dst;

	if (!s1)
		return (NULL);
	s = malloc ((ft_strlen(s1) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	dst = s;
	while (*s1)
		*dst++ = *s1++;
	*dst = '\0';
	return (s);
}

char	*ft_remain_lines(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
		{
			s++;
			return (((char *)s));
		}
		s++;
	}
	if ((unsigned char)c == 0 && *s == 0)
		return ((char *)s);
	return (NULL);
}
