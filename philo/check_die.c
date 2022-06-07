/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:01:18 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/21 17:36:49 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_philo(t_data data, long time, int i, int *iseat)
{
	pthread_mutex_lock(&data.statuses[i]);
	if (time - data.philos[i].time_last_eat > data.rule->time_die)
	{
		printf("%ld %d died\n", get_time(data.rule->time_start), \
			data.philos[i].id);
		return (-1);
	}
	if (data.philos[i].count_eat < data.rule->count_eat)
	{
		*iseat = 0;
	}
	pthread_mutex_unlock(&data.statuses[i]);
	return (0);
}

void	check_die(t_data data)
{
	struct timeval	now;
	long			time;
	int				iseat;
	int				i;

	while (1)
	{
		iseat = 1;
		i = 0;
		gettimeofday(&now, NULL);
		time = now.tv_sec * 1000 + now.tv_usec / 1000;
		while (i < data.philos_count)
		{	
			if (check_philo(data, time, i, &iseat) == -1)
				return ;
			i += 1;
		}
		if (data.rule->count_eat != -1 && iseat == 1)
		{
			return ;
		}
		usleep(250);
	}
}
