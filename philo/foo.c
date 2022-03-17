/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:57:12 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/17 21:35:27 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*foo(void *pointer)
{
	t_philo	*philo;
	t_rule	rule;
	int		id;

	philo = pointer;
	rule = *philo->rule;
	id = philo->id;
	while (rule.count_eat != 0)
	{
		printf("%5ld %d is eating\n", timee(rule.time), id);
		usleep(rule.time_eat * 1000);
		printf("%5ld %d is sleeping\n", timee(rule.time), id);
		usleep(rule.time_sleep * 1000);
		printf("%5ld %d is thinking\n", timee(rule.time), id);
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
// 	while (i < 10)
// 	{
// 		if (pthread_mutex_lock(&philo->left->mutex))
// 		{
// 			printf("Error: mutex lock\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		printf("%ldms %d has taken left  fork \n", timee(), philo->id + 1);
// 		if (pthread_mutex_lock(&philo->right->mutex))
// 		{
// 			printf("Error: mutex lock\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		printf("%ldms %d has taken right fork \n", timee(), philo->id + 1);
// 		printf("%ldms %d is  eating           \n", timee(), philo->id + 1);
// 		usleep(100000);
// 		if (pthread_mutex_unlock(&philo->left->mutex))
// 		{
// 			printf("Error: mutex lock\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (pthread_mutex_unlock(&philo->right->mutex))
// 		{
// 			printf("Error: mutex lock\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		printf("%ldms %d is  thinking         \n", timee(), philo->id + 1);
// 		usleep(100000);
// 		printf("%ldms %d is  sleeping         \n", timee(), philo->id + 1);
// 		usleep(100000);
// 		i += 1;
// 	}
// 	return (philo);
// }