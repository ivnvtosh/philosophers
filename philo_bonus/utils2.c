/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:08:09 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/21 18:00:00 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(long time)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - time);
}

void	ft_usleep(long time)
{
	struct timeval	now;
	long			start;

	gettimeofday(&now, NULL);
	start = now.tv_sec * 1000 + now.tv_usec / 1000;
	usleep(time * 800);
	while (now.tv_sec * 1000 + now.tv_usec / 1000 - start < time)
	{
		gettimeofday(&now, NULL);
		usleep(200);
	}
}
