/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:32:25 by cwon              #+#    #+#             */
/*   Updated: 2024/10/02 17:57:42 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

ssize_t	ft_strchr(const char *s, size_t i, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] == (c % 128))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	ptr = (char *)malloc(len + 1);
	i = 0;
	if (s && ptr)
	{
		while (i < len)
		{
			ptr[i] = s[i];
			i++;
		}
		ptr[i] = 0;
	}
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr)
	{
		while (s1[j])
			ptr[i++] = s1[j++];
		j = 0;
		while (s2[j])
			ptr[i++] = s2[j++];
		ptr[i] = 0;
	}
	return (ptr);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	total_len;
	size_t	i;

	if (!s)
		return (0);
	total_len = ft_strlen(s);
	if (start >= total_len)
		len = 0;
	else if (len >= total_len - start)
		len = total_len - start;
	ptr = (char *)malloc(len + 1);
	if (ptr)
	{
		i = 0;
		while (i < len)
			ptr[i++] = s[start++];
		ptr[i] = 0;
	}
	return (ptr);
}
