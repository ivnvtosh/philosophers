/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:01:18 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/28 17:14:40 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	bye(t_philo *philo, t_rule rule)
{
	sem_wait(philo->print);
	printf("%ld %d died\n", get_time(rule.time_start), philo->id);
	exit(EXIT_FAILURE);
}

int	check_die(t_philo *philo)
{
	struct timeval	now;
	t_rule			rule;
	long			time;
	int				is_eat;

	rule = *philo->rule;
	is_eat = 0;
	while (1)
	{
		sem_wait(philo->status);
		gettimeofday(&now, NULL);
		time = now.tv_sec * 1000 + now.tv_usec / 1000;
		if (time - philo->time_last_eat > rule.time_die)
			bye(philo, rule);
		if (is_eat != 1 && rule.count_eat != -1 && \
			philo->count_eat >= rule.count_eat)
		{
			sem_post(philo->all_eat);
			is_eat = 1;
		}
		sem_post(philo->status);
		usleep(250);
	}
}
