/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:32:02 by cwon              #+#    #+#             */
/*   Updated: 2024/10/20 17:41:04 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	flush(char **arr)
{
	if (arr && *arr)
	{
		free(*arr);
		*arr = 0;
	}
}

static void	extract_remaining(char **remaining, size_t i)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(*remaining);
	if (i + 1 < len)
	{
		temp = ft_substr(*remaining, i + 1, len - i - 1);
		free(*remaining);
		*remaining = ft_strdup(temp);
		free(temp);
	}
	else
		flush(remaining);
}

static ssize_t	extract_buffer(int fd, char **remaining)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(buffer);
		free(*remaining);
		*remaining = 0;
		return (-1);
	}
	if (bytes_read > 0)
	{
		buffer[bytes_read] = 0;
		if (*remaining)
		{
			temp = ft_strdup(*remaining);
			free(*remaining);
			*remaining = ft_strjoin(temp, buffer);
			free(temp);
		}
		else
			*remaining = ft_strdup(buffer);
	}
	free(buffer);
	return (bytes_read);
}

static char	*extract_line(int fd, char **remaining)
{
	char	*result;
	ssize_t	i;
	ssize_t	bytes_read;

	result = 0;
	i = ft_strchr(*remaining, 0, '\n');
	bytes_read = 1;
	while (i == -1 && bytes_read > 0)
	{
		bytes_read = extract_buffer(fd, remaining);
		i = ft_strchr(*remaining, i + 1, '\n');
	}
	if (bytes_read == -1)
	{
		free(result);
		free(*remaining);
		*remaining = 0;
		return (0);
	}
	if (i != -1)
	{
		result = ft_substr(*remaining, 0, i + 1);
		extract_remaining(remaining, (size_t)i);
	}
	else
	{
		result = ft_strdup(*remaining);
		flush(remaining);
	}
	return (result);
}
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*result;
	static char	*remaining;
	ssize_t		bytes_read;

	result = 0;
	bytes_read = extract_buffer(fd, &remaining);
	if (bytes_read == -1)
	{
		free(result);
		free(remaining);
		remaining = 0;
		return (0);
	}
	if (bytes_read > 0 || remaining)
		result = extract_line(fd, &remaining);
	return (result);
}
