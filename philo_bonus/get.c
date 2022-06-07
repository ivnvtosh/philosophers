/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:10:12 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/28 15:43:24 by ccamie           ###   ########.fr       */
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

pid_t	*get_process(int count)
{
	pid_t	*process;

	process = (pid_t *)malloc(count * sizeof(pid_t));
	if (process == NULL)
		return (NULL);
	return (process);
}
