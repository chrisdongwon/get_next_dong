/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:32:02 by cwon              #+#    #+#             */
/*   Updated: 2024/10/24 23:17:11 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

static void	flush(char *buffer, char **remaining)
{
	free(buffer);
	free(*remaining);
	*remaining = 0;
}

static void	extract_remaining(int fd, char **remaining)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (flush(buffer, remaining));
	bytes_read = 1;
	temp = 0;
	while (bytes_read && !ft_strchr(*remaining, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (flush(buffer, remaining));
		buffer[bytes_read] = 0;
		if (*remaining)
			temp = ft_strjoin(*remaining, buffer);
		else
			temp = ft_substr(buffer, 0, ft_strlen(buffer));
		free(*remaining);
		*remaining = temp;
	}
	free(buffer);
}

static char	*extract_line(char **remaining)
{
	size_t	i;
	char	*temp;
	char	*result;

	i = 0;
	if (!*remaining[i])
	{
		flush(0, remaining);
		return (0);
	}
	temp = ft_strchr(*remaining, '\n');
	if (!temp)
		i = ft_strlen(*remaining);
	else
		i = temp - *remaining + 1;
	result = ft_substr(*remaining, 0, i);
	temp = ft_substr(*remaining, i, ft_strlen(*remaining) - i);
	free(*remaining);
	*remaining = temp;
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*remaining;

	extract_remaining(fd, &remaining);
	if (!remaining)
		return (0);
	return (extract_line(&remaining));
}
