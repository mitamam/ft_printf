# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmasuda <mmasuda@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/30 10:18:56 by mmasuda           #+#    #+#              #
#    Updated: 2021/05/15 18:45:43 by mmasuda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS = ft_printf.c ft_printf_char.c ft_printf_hex.c ft_printf_int.c \
		ft_printf_utils.c ft_printf_utils_add.c ft_printf_unsigned_int.c \
		ft_printf_octal_percent.c ft_printf_libft.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:%.c=%.o)
RM = rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS) $(B_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
