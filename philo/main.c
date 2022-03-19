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

static int	start(t_rule *rule, t_philos *philos, int count)
{
	pthread_t	*potok;
	t_philos	*first;
	int			i;

	potok = (pthread_t *)malloc(sizeof(pthread_t) * count);
	if (potok == NULL)
		return (EXIT_FAILURE);
	i = 0;
	if (gettimeofday(&rule->time, NULL) == -1)
	{
		free(potok);
		return (EXIT_FAILURE);
	}
	first = philos;
	while (i < count)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&potok[i], NULL, foo1, philos->philo) != 0)
			{
				printf("Error: create\n");
				free(potok);
				return (EXIT_FAILURE);
			}
		}
		else
		{
			if (pthread_create(&potok[i], NULL, foo2, philos->philo) != 0)
			{
				printf("Error: create\n");
				free(potok);
				return (EXIT_FAILURE);
			}
		}
		philos = philos->next;
		i += 1;
	}
	

	struct timeval	now;
	usleep(rule->time_die * 1000 + 1000000);

	while (1)
	{
		philos = first;
		if (gettimeofday(&now, NULL) == -1)
		{
				printf("Error: time\n");
				free(potok);
				return (EXIT_FAILURE);
		}
		while (philos != NULL)
		{
			if ((now.tv_sec * 1000 + now.tv_usec / 1000) - (philos->philo->time_last_eat.tv_sec * 1000 + philos->philo->time_last_eat.tv_usec / 1000) > philos->philo->rule->time_die)
			{
				return (0);
			}
			philos = philos->next;
		}
	}



	
	// i = 0;
	// while (i < count)
	// {
	// 	if (pthread_join(potok[i], NULL))
	// 	{
	// 		free(potok);
	// 		printf("Error: join\n");
	// 		return (EXIT_FAILURE);
	// 	}
	// 	// if (pthread_detach(potok[i], NULL))
	// 	// {
	// 	// 	free(potok);
	// 	// 	printf("Error: join\n");
	// 	// 	return (EXIT_FAILURE);
	// 	// }
	// 	i += 1;
	// }
	free(potok);
	return (EXIT_SUCCESS);
}

static int	philo(int argc, char **argv)
{
	t_data	data;

	if (parser(&data, argc, argv))
	{
		return (my_error("Error\n"));
	}
	if (start(&data.rule, data.philos, data.philo_count))
	{
		my_forkclear(&data.forks);
		my_philoclear(&data.philos);
		return (my_error("Error\n"));
	}
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
