/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:32:02 by cwon              #+#    #+#             */
/*   Updated: 2024/10/02 00:07:45 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Parsing [A \n B \0] with buffer_size = 1

buffer:		[\n]
result:		[A \n]
remaining:	[]

observations:
1. refill buffer if and only if remaining has no newline.
	otherwise, result comes from remaining.
	doing so will only require malloc of buffer once in the start.
2. always start by attaching buffer to remaining.
	then, only parse on remaining for extraction.
*/

#include "get_next_line.h"

static ssize_t	buffer_prep(int fd, char **buffer, char **remaining)
{
	char	*temp;
	ssize_t	bytes_read;

	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		if (*remaining)
		{
			temp = ft_strdup(*remaining);
			free(*remaining);
			*remaining = ft_strjoin(temp, *buffer);
			free(temp);
		}
		else
			*remaining = ft_strdup(*buffer);
	}
	return (bytes_read);
}

static void parse(int fd, char **buffer, char **result, char **remaining)
{
	ssize_t	i;
	char	*temp;

	i = ft_strchr(*remaining, '\n');
	if (i != -1)
	{
		*result = ft_substr(*remaining, 0, i + 1);
		if (i + 1 < BUFFER_SIZE)
		{
			temp = ft_substr(*remaining, i + 1, BUFFER_SIZE - i);
			free(*remaining);
			*remaining = ft_strdup(temp);
			free(temp);
		}
		else if(*remaining)
		{
			free(*remaining);
			*remaining = 0;
		}
	}
	else if (buffer_prep(fd, buffer, remaining) > 0)
		parse(fd, buffer, result, remaining);
	else if (*remaining)
		*result = *remaining;
}

char	*get_next_line(int fd)
{
	char		*result;
	char		*buffer;
	static char	*remaining;

	result = 0;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	buffer[BUFFER_SIZE] = 0;
	if (buffer_prep(fd, &buffer, &remaining) > 0)
		parse(fd, &buffer, &result, &remaining);
	free(buffer);
	return (result);
}
