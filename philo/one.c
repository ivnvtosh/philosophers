/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:13:21 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/23 20:54:35 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_one(void *pointer)
{
	t_philo			*philo;
	t_rule			rule;
	long			time;

	philo = pointer;
	rule = *philo->rule;
	time = get_time(rule.time);
	if (time == -1)
		return (NULL);
	printf("%5ld %3d has taken left fork\n", time, philo->id);
	usleep(rule.time_die * 1001);
	return (pointer);
}


static int	check_is_live(t_rule *rule, t_philos *philos)
{
	struct timeval	now;
	long			time;

	while (1)
	{
		if (gettimeofday(&now, NULL) == -1)
			return (-1);
		time = now.tv_sec * 1000 + now.tv_usec / 1000;
		if (time - philos->philo->time_last_eat > rule->time_die)
		{
			printf("WTF: %ld\n", time - philos->philo->time_last_eat);
			return (EXIT_SUCCESS);
		}
		if (usleep(10000) == -1)
			return (-1);
	}
	return (EXIT_SUCCESS);
}

int	start_one(t_rule *rule, t_philos *philos, int count, pthread_t *potok)
{
	struct timeval	time;

	(void)count;
	if (gettimeofday(&time, NULL) == -1)
		return (EXIT_FAILURE);
	rule->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (pthread_create(&potok[0], NULL, one_one, philos->philo) != 0)
		return (-1);
	philos->philo->time_last_eat = rule->time;
	if (check_is_live(rule, philos) == -1)
		return (EXIT_FAILURE);
	pthread_detach(potok[0]);
	return (EXIT_SUCCESS);
}
