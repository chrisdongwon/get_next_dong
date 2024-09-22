/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:32:02 by cwon              #+#    #+#             */
/*   Updated: 2024/09/22 17:50:06 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char*	buffer;
	static char*	ptr;
	static size_t	bytes_read;

	if (!ptr)
	{
		buffer = (char *)malloc(BUFFER_SIZE);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (!bytes_read)
		return (0);
	
	if (ptr == buffer + BUFFER_SIZE)
	{
		free(buffer);
		ptr = 0;
	}
}
