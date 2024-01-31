# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 11:32:07 by jsarda            #+#    #+#              #
#    Updated: 2024/01/30 16:35:34 by jsarda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client
NAMESV = server

SRCS =  ./src/client.c
SRCSSV = ./src/server.c

OBJS = ${SRCS:.c=.o}
OBJSSV = ${SRCSSV:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

all: ${NAME} ${NAMESV}
${NAME} : ${OBJS}
	@${MAKE} -C ./libft
	@${CC} ${CFLAGS} ${OBJS} ./libft/libft.a -o ${NAME}

${NAMESV}: ${OBJSSV}
	@${CC} ${CFLAGS} ${OBJSSV} ./libft/libft.a -o ${NAMESV}

clean:
	@${MAKE} -C ./libft fclean
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME} ${NAMESV}

re: fclean all

.PHONY: all clean fclean re
