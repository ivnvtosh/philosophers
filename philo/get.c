/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:10:12 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/28 15:41:57 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_rule	*get_rule(int count, char **parameters)
{
	t_rule	*rule;

	rule = (t_rule *)malloc(sizeof(t_rule));
	if (rule == NULL)
		return (NULL);
	rule->time_die = ft_atoi(parameters[1]);
	rule->time_eat = ft_atoi(parameters[2]);
	rule->time_sleep = ft_atoi(parameters[3]);
	if (rule->time_die <= 0 || rule->time_eat <= 0 || rule->time_sleep <= 0)
	{
		free(rule);
		return (NULL);
	}
	if (count == 5)
	{
		rule->count_eat = ft_atoi(parameters[4]);
		if (rule->count_eat <= 0)
		{
			free(rule);
			return (NULL);
		}
	}
	else
		rule->count_eat = -1;
	return (rule);
}

pthread_mutex_t	*get_forks(int count)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(count * sizeof(pthread_mutex_t));
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			remove_forks(&forks, i - 1);
			return (NULL);
		}
		i += 1;
	}
	return (forks);
}

pthread_mutex_t	*get_statuses(int count)
{
	pthread_mutex_t	*statuses;
	int				i;

	statuses = (pthread_mutex_t *)malloc(count * sizeof(pthread_mutex_t));
	if (statuses == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&statuses[i], NULL) != 0)
		{
			remove_statuses(&statuses, i - 1);
			return (NULL);
		}
		i += 1;
	}
	return (statuses);
}

t_philo	*get_philos(int count, t_rule *rule)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(count * sizeof(t_philo));
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		philos[i].id = i + 1;
		philos[i].count_eat = 0;
		philos[i].rule = rule;
		i += 1;
	}
	return (philos);
}

pthread_t	*get_threads(int count)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(count * sizeof(pthread_t));
	if (threads == NULL)
		return (NULL);
	return (threads);
}
