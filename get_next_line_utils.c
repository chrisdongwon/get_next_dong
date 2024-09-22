/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:32:25 by cwon              #+#    #+#             */
/*   Updated: 2024/09/22 17:46:49 by cwon             ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s) + 1;
	while (i < len)
	{
		if (s[i] == (c % 128))
			return ((char *)(s + i));
		i++;
	}
	return (0);
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
