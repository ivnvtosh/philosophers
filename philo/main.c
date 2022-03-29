/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 04:39:09 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/29 20:44:32 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		parser(t_data *data, int argc, char **argv);
void	*foo1(void *pointer);
void	*foo2(void *pointer);

int	philos_create(t_rule *rule, t_philos *philos, int count, pthread_t *potok)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&potok[i], NULL, foo1, philos->philo) != 0)
				return (-1);
		}
		else
		{
			if (pthread_create(&potok[i], NULL, foo2, philos->philo) != 0)
				return (-1);
		}
		philos->philo->time_last_eat = rule->time;
		philos = philos->next;
		i += 1;
	}
	return (EXIT_SUCCESS);
}

static int	check_is_live(t_rule *rule, t_philos *philos)
{
	struct timeval	now;
	long			time;
	t_philos		*first;

	first = philos;
	while (1)
	{
		philos = first;
		if (gettimeofday(&now, NULL) == -1)
			return (-1);
		time = now.tv_sec * 1000 + now.tv_usec / 1000;
		while (philos != NULL)
		{
			if (pthread_mutex_lock(&philos->philo->status))
				return (EXIT_SUCCESS);
			if (time - philos->philo->time_last_eat > rule->time_die)
			{
				printf("WTF: %ld\n", time - philos->philo->time_last_eat);
				return (EXIT_SUCCESS);
			}
			if (pthread_mutex_unlock(&philos->philo->status))
				return (EXIT_SUCCESS);
			philos = philos->next;
		}
		if (usleep(10000) == -1)
			return (-1);
	}
	return (EXIT_SUCCESS);
}

static int	start(t_rule *rule, t_philos *philos, int count, pthread_t *potok)
{
	struct timeval	time;
	int				i;

	if (gettimeofday(&time, NULL) == -1)
		return (EXIT_FAILURE);
	rule->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (philos_create(rule, philos, count, potok) != -1)
	{
		if (check_is_live(rule, philos) == -1)
			return (EXIT_FAILURE);
	}
	i = 0;
	while (i < count)
	{
		pthread_detach(potok[i]);
		i += 1;
	}
	return (EXIT_SUCCESS);
}

int	start_one(t_rule *rule, t_philos *philos, int count, pthread_t *potok);

static int	philo(int argc, char **argv)
{
	t_data		data;
	pthread_t	*potok;

	if (parser(&data, argc, argv))
	{
		return (my_error("Error\n"));
	}
	potok = (pthread_t *)malloc(sizeof(pthread_t) * data.philo_count);
	if (potok == NULL)
	{
		my_forkclear(&data.forks);
		my_philoclear(&data.philos);
		return (my_error("Error\n"));
	}
	// if (data.philo_count == 1)
	// 	start_one(&data.rule, data.philos, data.philo_count, potok);
	// else
		start(&data.rule, data.philos, data.philo_count, potok);
	free(potok);
	my_forkclear(&data.forks);
	my_philoclear(&data.philos);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		return (philo(argc, ++argv));
	}
	else
	{
		return (my_error("Error\n"));
	}
}
