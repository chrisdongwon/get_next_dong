/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:32:25 by cwon              #+#    #+#             */
/*   Updated: 2024/10/24 23:23:15 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	result;

	result = 0;
	if (s)
	{
		while (s[result])
			result++;
	}
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	if (s)
	{
		i = 0;
		len = ft_strlen(s) + 1;
		while (i < len)
		{
			if (s[i] == (c % 128))
				return ((char *)(s + i));
			i++;
		}
	}
	return (0);
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
