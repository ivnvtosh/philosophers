/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:57:12 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/19 22:55:24 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*foo1(void *pointer)
{
	t_philo	*philo;
	t_rule	rule;
	int		id;

	philo = pointer;
	rule = *philo->rule;
	id = philo->id;
	while (rule.count_eat != 0)
	{
		if (pthread_mutex_lock(&philo->left))
		{
			printf("Error: mutex lock\n");
			exit(EXIT_FAILURE);
		}
		printf("%5ld %3d has taken left fork\n", get_time(rule.time), id);
		if (pthread_mutex_lock(&philo->right))
		{
			printf("Error: mutex lock\n");
			exit(EXIT_FAILURE);
		}
		printf("%5ld %3d has taken right fork\n", get_time(rule.time), id);
		printf("%5ld %3d is eating\n", get_time(rule.time), id);
		usleep(rule.time_eat * 1000);
		if (pthread_mutex_unlock(&philo->left))
		{
			printf("Error: mutex lock\n");
			exit(EXIT_FAILURE);
		}
		if (pthread_mutex_unlock(&philo->right))
		{
			printf("Error: mutex lock\n");
			exit(EXIT_FAILURE);
		}
		if (gettimeofday(&philo->time_last_eat, NULL) == -1)
		{
			printf("Error: time last\n");
			exit(EXIT_FAILURE);
		}
		printf("%5ld %3d is sleeping\n", get_time(rule.time), id);
		usleep(rule.time_sleep * 1000);
		printf("%5ld %3d is thinking\n", get_time(rule.time), id);
		rule.count_eat -= 1;
	}
	return (pointer);
}

void	*foo2(void *pointer)
{
	t_philo	*philo;
	t_rule	rule;
	int		id;

	philo = pointer;
	rule = *philo->rule;
	id = philo->id;
	while (rule.count_eat != 0)
	{
		printf("%5ld %3d is sleeping\n", get_time(rule.time), id);
		usleep(rule.time_sleep * 1000);
		printf("%5ld %3d is thinking\n", get_time(rule.time), id);
		if (pthread_mutex_lock(&philo->left))
		{
			printf("Error: mutex lock\n");
			exit(EXIT_FAILURE);
		}
		printf("%5ld %3d has taken left fork\n", get_time(rule.time), id);
		if (pthread_mutex_lock(&philo->right))
		{
			printf("Error: mutex lock\n");
			exit(EXIT_FAILURE);
		}
		printf("%5ld %3d has taken right fork\n", get_time(rule.time), id);
		printf("%5ld %3d is eating\n", get_time(rule.time), id);
		usleep(rule.time_eat * 1000);
		if (pthread_mutex_unlock(&philo->left))
		{
			printf("Error: mutex lock\n");
			exit(EXIT_FAILURE);
		}
		if (pthread_mutex_unlock(&philo->right))
		{
			printf("Error: mutex lock\n");
			exit(EXIT_FAILURE);
		}
		if (gettimeofday(&philo->time_last_eat, NULL) == -1)
		{
			printf("Error: time last\n");
			exit(EXIT_FAILURE);
		}
		rule.count_eat -= 1;
	}
	return (pointer);
}

// void	*foo(void *pointer)
// {
// 	t_philo			*philo;
// 	// struct timeval	now;

// 	philo = pointer;


// 	int	i;

// 	i = 0;
	// while (i < 10)
	// {
	// 	if (pthread_mutex_lock(&philo->left->mutex))
	// 	{
	// 		printf("Error: mutex lock\n");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	printf("%ldms %d has taken left  fork \n", get_time(), philo->id + 1);
	// 	if (pthread_mutex_lock(&philo->right->mutex))
	// 	{
	// 		printf("Error: mutex lock\n");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	printf("%ldms %d has taken right fork \n", get_time(), philo->id + 1);
	// 	printf("%ldms %d is  eating           \n", get_time(), philo->id + 1);
	// 	usleep(100000);
	// 	if (pthread_mutex_unlock(&philo->left->mutex))
	// 	{
	// 		printf("Error: mutex lock\n");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	if (pthread_mutex_unlock(&philo->right->mutex))
	// 	{
	// 		printf("Error: mutex lock\n");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	printf("%ldms %d is  sleeping         \n", get_time(), philo->id + 1);
	// 	usleep(100000);
	// 	printf("%ldms %d is  thinking         \n", get_time(), philo->id + 1);
	// 	i += 1;
	// }
	// return (philo);
// }