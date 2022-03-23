/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:05:16 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/23 21:46:14 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*my_philolast(t_philos *philos)
{
	while (philos->next != NULL)
		philos = philos->next;
	return (philos);
}

void	my_philoadd_back(t_philos **philos, t_philos *new)
{
	if (*philos == NULL)
		*philos = new;
	else
		my_philolast(*philos)->next = new;
}

void	my_philoclear(t_philos **philos)
{
	t_philos	*prev;
	t_philos	*elem;

	elem = *philos;
	*philos = NULL;
	while (elem != NULL)
	{
		prev = elem;
		elem = elem->next;
		pthread_mutex_destroy(&prev->philo->status);		//	wtf!!!!
		free(prev->philo);
		free(prev);
	}
}

t_philos	*my_philonew(int id, t_rule *rule)
{
	t_philos	*philos;
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	philos = (t_philos *)malloc(sizeof(t_philos));
	if (philo == NULL || philos == NULL)
	{
		free(philo);
		free(philos);
		return (NULL);
	}
	if (pthread_mutex_init(&philo->status, NULL) != 0)
	{
		free(philo);
		free(philos);
		return (NULL);
	}
	philo->id = id;
	philo->time_last_eat = 0;
	philo->rule = rule;
	philos->philo = philo;
	philos->next = NULL;
	return (philos);
}
