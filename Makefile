# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzizi <tzizi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/06 12:48:00 by tzizi            #+#    #+#              #
#    Updated: 2026/01/06 12:48:00 by tzizi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CXX = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRC = srcs/main.cpp srcs/client/client.cpp srcs/server/server.cpp \

OBJS = ${SRC:.cpp=.o}

all: ${NAME}

${NAME}: ${OBJS}
	mkdir srcs/objs
	${CXX} ${CPPFLAGS} ${OBJS} -o ${NAME}
	mv srcs/*.o srcs/client/*.o srcs/server/*.o srcs/objs

clean:
	rm -rf srcs/objs

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all re clean fclean