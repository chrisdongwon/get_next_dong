/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:32:02 by cwon              #+#    #+#             */
/*   Updated: 2024/10/28 01:05:12 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*flush(char **remaining, char *buffer, int success)
{
	char	*result;

	free(buffer);
	if (!*remaining)
		return (0);
	result = 0;
	if (success)
		result = ft_substr(*remaining, 0, ft_strlen(*remaining));
	free(*remaining);
	*remaining = 0;
	return (result);
}

static char	*extract_remaining(char *remaining, char *buffer)
{
	char	*result;
	char	*temp;

	if (!remaining && buffer)
		return (ft_substr(buffer, 0, ft_strlen(buffer)));
	temp = ft_substr(remaining, 0, ft_strlen(remaining));
	if (!temp)
		return (flush(&remaining, 0, 0));
	result = ft_strjoin(temp, buffer);
	flush(&remaining, temp, 0);
	return (result);
}

static char	*update_remaining(char *remaining)
{
	char	*result;
	ssize_t	i;

	if (!remaining)
		return (0);
	i = ft_strchr(remaining, '\n');
	if (!remaining[i + 1])
		return (flush(&remaining, 0, 0));
	result = ft_substr(remaining, i + 1, ft_strlen(remaining));
	flush(&remaining, 0, 0);
	return (result);
}

static char	*extract_line(int fd, char *buffer, char **remaining)
{
	char	*result;
	ssize_t	bytes_read;
	ssize_t	end;

	bytes_read = -1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1 || (!bytes_read && !*remaining))
			return (flush(remaining, buffer, 0));
		buffer[bytes_read] = 0;
		*remaining = extract_remaining(*remaining, buffer);
		end = ft_strchr(*remaining, '\n');
		if (end != -1)
		{
			result = ft_substr(*remaining, 0, end + 1);
			if (!result)
				return (flush(remaining, buffer, 0));
			*remaining = update_remaining(*remaining);
			free(buffer);
			return (result);
		}
	}
	return (flush(remaining, buffer, 1));
}

// ulimit -Hn shows the hard limit
// 1048576 on my system
char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*remaining[1048576];

	if (fd < 0)
		return (0);
	if (BUFFER_SIZE <= 0)
		return (flush(&remaining[fd], 0, 0));
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (flush(&remaining[fd], 0, 0));
	return (extract_line(fd, buffer, &remaining[fd]));
}
