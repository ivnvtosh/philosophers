# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 18:07:59 by ccamie            #+#    #+#              #
#    Updated: 2022/04/28 15:22:48 by ccamie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

HEADER			=	philosophers.h

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -f

SOURCE			=	check_die.c		\
					check.c			\
					get.c			\
					launch_philosophers.c	\
					launch.c		\
					life.c			\
					main.c			\
					parser.c		\
					philosophers.c	\
					remove.c		\
					utils1.c		\
					utils2.c		\
					utils3.c		\

OBJECT			=	$(SOURCE:.c=.o)

.PHONY			:	all clean fclean re

all				:	$(NAME)

$(NAME)			:	$(OBJECT)
					$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)

%.o				:	%.c $(HEADER)
					$(CC) $(CFLAGS) -c $< -o $@

clean			:
					$(RM) $(OBJECT)

fclean			:	clean
					$(RM) $(NAME)

re				:	fclean all
