# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 13:46:01 by jsarda            #+#    #+#              #
#    Updated: 2024/01/30 16:27:54 by jsarda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_print_char.c ft_printf_nbr_unsigned.c ft_print_nbr.c ft_print_ptr_hexa.c ft_print_ptr.c ft_print_str.c ft_printf.c ft_putchar_fd.c ft_putnbr_fd.c ft_eval_format.c
OBJS = $(SRCS:.c=.o)

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o : %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

bonus: $(OBJS)
	ar rcs $(NAME) $(OBJS)

.PHONY: all clean fclean re bonus
