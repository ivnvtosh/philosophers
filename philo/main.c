/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 04:39:09 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/19 23:06:50 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		parser(t_data *data, int argc, char **argv);
void	*foo1(void *pointer);
void	*foo2(void *pointer);

static int	philos_create(t_rule *rule, t_philos *philos, int count, pthread_t *potok)
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
	t_philos		*first;

	first = philos;
	while (1)
	{
		philos = first;
		if (gettimeofday(&now, NULL) == -1)
			return (-1);
		while (philos != NULL)
		{
			if ((now.tv_sec * 1000 + now.tv_usec / 1000) - philos->philo->time_last_eat > rule->time_die)
			{
				printf("WTF: %ld\n", (now.tv_sec * 1000 + now.tv_usec / 1000) - philos->philo->time_last_eat);
				return (EXIT_SUCCESS);
			}
			philos = philos->next;
		}
		usleep(10000);
	}
	return (EXIT_SUCCESS);
}

static int	start(t_rule *rule, t_philos *philos, int count, pthread_t *potok)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (EXIT_FAILURE);
	rule->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (philos_create(rule, philos, count, potok) == -1)
		return (EXIT_FAILURE);
	if (check_is_live(rule, philos) == -1)
		return (EXIT_FAILURE);
	int	i;

	i = 0;
	while (i < count)
	{
		// if (pthread_join(potok[i], NULL))
		// {
		// 	free(potok);
		// 	printf("Error: join\n");
		// 	return (EXIT_FAILURE);
		// }
		pthread_detach(potok[i]);
		i += 1;
	}
	return (EXIT_SUCCESS);
}

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
	if (start(&data.rule, data.philos, data.philo_count, potok))
	{
		free(potok);
		my_forkclear(&data.forks);
		my_philoclear(&data.philos);
		return (my_error("Error\n"));
	}
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
