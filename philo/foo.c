/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:57:12 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/01 21:56:27 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	is_thinking(t_philo *philo, t_rule rule)
// {
// 	long	time;

// 	time = get_time(rule.time);
// 	if (time == -1)
// 		return (EXIT_FAILURE);
// 	printf("%5ld %3d is thinking\n", time, philo->id);
// 	return (EXIT_SUCCESS);
// }

// static int	is_sleeping(t_philo *philo, t_rule rule)
// {
// 	long	time;

// 	time = get_time(rule.time);
// 	if (time == -1)
// 		return (EXIT_FAILURE);
// 	printf("%5ld %3d is sleeping\n", time, philo->id);
// 	if (ft_usleep(rule.time_sleep) == -1)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

// static int	is_eating(t_philo *philo, t_rule rule)
// {
// 	struct timeval	now;
// 	long			time;

// 	time = get_time(rule.time);
// 	if (time == -1)
// 		return (EXIT_FAILURE);
// 	printf("%5ld %3d has taken right fork\n", time, philo->id);
// 	time = get_time(rule.time);
// 	if (time == -1)
// 		return (EXIT_FAILURE);
// 	printf("%5ld %3d is eating\n", time, philo->id);
// 	if (ft_usleep(rule.time_eat) == -1)
// 		return (EXIT_FAILURE);
// 	if (pthread_mutex_unlock(philo->left) || \
// 		pthread_mutex_unlock(philo->right))
// 		return (EXIT_FAILURE);
// 	if (gettimeofday(&now, NULL) == -1)
// 		return (EXIT_FAILURE);
// 	if (pthread_mutex_lock(&philo->status))
// 		return (EXIT_FAILURE);
// 	philo->time_last_eat = now.tv_sec * 1000 + now.tv_usec / 1000;
// 	if (pthread_mutex_unlock(&philo->status))
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

// void	*foo1(void *pointer)
// {
// 	t_philo			*philo;
// 	t_rule			rule;
// 	long			time;

// 	philo = pointer;
// 	rule = *philo->rule;
// 	while (rule.count_eat != 0)
// 	{
// 		if (is_thinking(philo, rule))
// 			return (NULL);
// 		if (pthread_mutex_lock(philo->left))
// 			return (NULL);
// 		time = get_time(rule.time);
// 		if (time == -1)
// 			return (NULL);
// 		printf("%5ld %3d has taken left fork\n", time, philo->id);
// 		if (pthread_mutex_lock(philo->right))
// 			return (NULL);
// 		if (is_eating(philo, rule))
// 			return (NULL);
// 		if (is_sleeping(philo, rule))
// 			return (NULL);
// 		rule.count_eat -= 1;
// 	}
// 	return (pointer);
// }

// void	*foo2(void *pointer)
// {
// 	t_philo			*philo;
// 	t_rule			rule;
// 	long			time;

// 	philo = pointer;
// 	rule = *philo->rule;
// 	while (rule.count_eat != 0)
// 	{
// 		if (is_sleeping(philo, rule))
// 			return (NULL);
// 		if (is_thinking(philo, rule))
// 			return (NULL);
// 		if (pthread_mutex_lock(philo->left))
// 			return (NULL);
// 		time = get_time(rule.time);
// 		if (time == -1)
// 			return (NULL);
// 		printf("%5ld %3d has taken left fork\n", time, philo->id);
// 		if (pthread_mutex_lock(philo->right))
// 			return (NULL);
// 		if (is_eating(philo, rule))
// 			return (NULL);
// 		rule.count_eat -= 1;
// 	}
// 	return (pointer);
// }

static void	is_thinking(t_philo *philo, t_rule rule)
{
	printf("%5ld %3d is thinking\n", get_time(rule.time), philo->id);
}

static void	is_sleeping(t_philo *philo, t_rule rule)
{
	printf("%5ld %3d is sleeping\n", get_time(rule.time), philo->id);
	usleep(rule.time_sleep * 1000);
}

static void	is_eating(t_philo *philo, t_rule rule)
{
	struct timeval	now;

	pthread_mutex_lock(philo->left);
	printf("%5ld %3d has taken a left fork\n", get_time(rule.time), philo->id);
	pthread_mutex_lock(philo->right);
	printf("%5ld %3d has taken a right fork\n", get_time(rule.time), philo->id);
	printf("%5ld %3d is eating\n", get_time(rule.time), philo->id);
	usleep(rule.time_eat * 1000);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&philo->status);
	philo->time_last_eat = now.tv_sec * 1000 + now.tv_usec / 1000;
	pthread_mutex_unlock(&philo->status);
}

void	*foo1(void *pointer)
{
	t_philo			*philo;
	t_rule			rule;

	philo = pointer;
	rule = *philo->rule;
	while (rule.count_eat != 0)
	{
		is_thinking(philo, rule);
		is_eating(philo, rule);
		is_sleeping(philo, rule);
		rule.count_eat -= 1;
	}
	return (pointer);
}

void	*foo2(void *pointer)
{
	t_philo			*philo;
	t_rule			rule;

	philo = pointer;
	rule = *philo->rule;
	while (rule.count_eat != 0)
	{
		is_sleeping(philo, rule);
		is_thinking(philo, rule);
		is_eating(philo, rule);
		rule.count_eat -= 1;
	}
	return (pointer);
}
