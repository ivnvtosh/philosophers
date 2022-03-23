/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:57:12 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/23 21:44:22 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_thinking(t_philo *philo, t_rule rule)
{
	long	time;

	time = get_time(rule.time);
	if (time == -1)
		return (EXIT_FAILURE);
	printf("%5ld %3d is thinking\n", time, philo->id);
	return (EXIT_SUCCESS);
}

static int	is_sleeping(t_philo *philo, t_rule rule)
{
	long	time;

	time = get_time(rule.time);
	if (time == -1)
		return (EXIT_FAILURE);
	printf("%5ld %3d is sleeping\n", time, philo->id);
	if (usleep(rule.time_sleep * 1000) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	is_eating(t_philo *philo, t_rule rule)
{
	struct timeval	now;
	long			time;

	time = get_time(rule.time);
	if (time == -1)
		return (EXIT_FAILURE);
	printf("%5ld %3d has taken right fork\n", time, philo->id);
	time = get_time(rule.time);
	if (time == -1)
		return (EXIT_FAILURE);
	printf("%5ld %3d is eating\n", time, philo->id);
	if (usleep(rule.time_eat * 1000) == -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(&philo->left) || \
		pthread_mutex_unlock(&philo->right))
		return (EXIT_FAILURE);
	if (gettimeofday(&now, NULL) == -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(&philo->status))
		return (EXIT_FAILURE);
	philo->time_last_eat = now.tv_sec * 1000 + now.tv_usec / 1000;
	if (pthread_mutex_unlock(&philo->status))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*foo1(void *pointer)
{
	t_philo			*philo;
	t_rule			rule;
	long			time;

	philo = pointer;
	rule = *philo->rule;
	while (rule.count_eat != 0)
	{
		if (is_thinking(philo, rule))
			return (NULL);
		if (pthread_mutex_lock(&philo->left))
			return (NULL);
		time = get_time(rule.time);
		if (time == -1)
			return (NULL);
		printf("%5ld %3d has taken left fork\n", time, philo->id);
		if (pthread_mutex_lock(&philo->right))
			return (NULL);
		if (is_eating(philo, rule))
			return (NULL);
		if (is_sleeping(philo, rule))
			return (NULL);
		rule.count_eat -= 1;
	}
	return (pointer);
}

void	*foo2(void *pointer)
{
	t_philo			*philo;
	t_rule			rule;
	long			time;

	philo = pointer;
	rule = *philo->rule;
	while (rule.count_eat != 0)
	{
		if (is_sleeping(philo, rule))
			return (NULL);
		if (is_thinking(philo, rule))
			return (NULL);
		if (pthread_mutex_lock(&philo->left))
			return (NULL);
		time = get_time(rule.time);
		if (time == -1)
			return (NULL);
		printf("%5ld %3d has taken left fork\n", time, philo->id);
		if (pthread_mutex_lock(&philo->right))
			return (NULL);
		if (is_eating(philo, rule))
			return (NULL);
		rule.count_eat -= 1;
	}
	return (pointer);
}
