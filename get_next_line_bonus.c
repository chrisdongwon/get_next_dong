/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line _bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:32:02 by cwon              #+#    #+#             */
/*   Updated: 2024/10/26 18:26:17 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	flush(char *buffer, char **remaining)
{
	free(buffer);
	free(*remaining);
	*remaining = 0;
}

static void	extract_remaining(int fd, char **remaining, ssize_t *bytes_read)
{
	char	*buffer;
	char	*temp;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (flush(buffer, remaining));
	*bytes_read = -1;
	while (*bytes_read && !ft_strchr(*remaining, '\n'))
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read == -1)
			return (flush(buffer, remaining));
		buffer[*bytes_read] = 0;
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

// hard limit on file descriptors: 1048576
// terminal command: ulimit -n -H
char	*get_next_line(int fd)
{
	static char	*remaining[1048576];
	char		*result;
	ssize_t		bytes_read;

	bytes_read = -1;
	extract_remaining(fd, &remaining[fd], &bytes_read);
	if (!remaining[fd])
		return (0);
	result = extract_line(&remaining[fd]);
	return (result);
}
