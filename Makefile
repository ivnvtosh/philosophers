# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 05:00:09 by ccamie            #+#    #+#              #
#    Updated: 2022/03/12 05:05:01 by ccamie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY		:	all clean fclean re bonus rebonus

all			:	object
				make -C philo all

# bonus		:	object
# 				make -C src_bonus all

object		:
				mkdir object

clean		:
				make -C philo clean
#				make -C philo_bonus clean
				rmdir object

fclean		:	clean
				make -C src fclean
#				make -C philo_bonus fclean
				
re			:	fclean all

rebonus		:	fclean bonus
