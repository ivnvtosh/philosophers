/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:36:33 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/28 15:39:55 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	is_sleeping(t_philo *philo, t_rule rule)
{
	printf("%ld %d is sleeping\n", get_time(rule.time_start), philo->id);
	ft_usleep(rule.time_sleep);
}

static void	is_eating(t_philo *philo, t_rule rule)
{
	struct timeval	now;

	pthread_mutex_lock(philo->left);
	printf("%ld %d has taken a fork\n", get_time(rule.time_start), philo->id);
	pthread_mutex_lock(philo->right);
	printf("%ld %d has taken a fork\n", get_time(rule.time_start), philo->id);
	pthread_mutex_lock(philo->status);
	gettimeofday(&now, NULL);
	philo->time_last_eat = now.tv_sec * 1000 + now.tv_usec / 1000;
	pthread_mutex_unlock(philo->status);
	printf("%ld %d is eating\n", get_time(rule.time_start), philo->id);
	gettimeofday(&now, NULL);
	ft_usleep(rule.time_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_lock(philo->status);
	philo->count_eat += 1;
	pthread_mutex_unlock(philo->status);
}

long	wait_all(long start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	while (now.tv_sec * 1000 + now.tv_usec / 1000 - start < 100)
	{
		gettimeofday(&now, NULL);
		usleep(200);
	}
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	*the_life_of_a_philosopher_1(void *pointer)
{
	t_philo	*philo;
	t_rule	rule;

	philo = pointer;
	rule = *philo->rule;
	pthread_mutex_lock(philo->status);
	rule.time_start = wait_all(rule.time_start);
	philo->time_last_eat = rule.time_start;
	pthread_mutex_unlock(philo->status);
	while (1)
	{
		is_eating(philo, rule);
		is_sleeping(philo, rule);
		printf("%ld %d is thinking\n", get_time(rule.time_start), philo->id);
	}
	return (NULL);
}

void	*the_life_of_a_philosopher_2(void *pointer)
{
	t_philo	*philo;
	t_rule	rule;

	philo = pointer;
	rule = *philo->rule;
	pthread_mutex_lock(philo->status);
	rule.time_start = wait_all(rule.time_start);
	philo->time_last_eat = rule.time_start;
	pthread_mutex_unlock(philo->status);
	while (1)
	{
		is_sleeping(philo, rule);
		printf("%ld %d is thinking\n", get_time(rule.time_start), philo->id);
		is_eating(philo, rule);
	}
	return (NULL);
}
