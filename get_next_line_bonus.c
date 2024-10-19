/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 22:28:32 by cwon              #+#    #+#             */
/*   Updated: 2024/10/02 22:41:41 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*result;
	static char	*remaining;

	result = 0;
	if (extract_buffer(fd, &remaining) > 0 || remaining)
		result = extract_line(fd, &remaining);
	return (result);
}
