# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/22 16:02:01 by cwon              #+#    #+#              #
#    Updated: 2024/09/22 17:24:04 by cwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .c .o

NAME = get_next_line

CC = cc
CFLAGS = -Wall -Wextra -Werror -D

buffer_size = 42

src = get_next_line.c get_next_line_utils.c

obj = $(src:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) BUFFER_SIZE=$(buffer_size) -o $(NAME) $(src)

clean:
	rm -f $(obj)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re