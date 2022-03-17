# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 05:02:28 by ccamie            #+#    #+#              #
#    Updated: 2022/03/17 19:24:06 by ccamie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

HEADER			=	philo.h

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -f

SOURCE			=	foo.c		\
					check.c		\
					main.c		\
					my_fork.c	\
					my_philo.c	\
					parser.c	\
					utils1.c	\
					utils2.c	\

OBJECT			=	$(addprefix ../object/, $(SOURCE:.c=.o))

.PHONY			:	all clean fclean re

all				:	$(NAME)

$(NAME)			:	$(OBJECT)
					$(CC) $(OBJECT) -o $(NAME)

../object/%.o	:	%.c $(HEADER)
					$(CC) $(CFLAGS) -c $< -o $@

clean			:
					$(RM) $(OBJECT)

fclean			:	clean
					$(RM) $(NAME)

re				:	fclean all
