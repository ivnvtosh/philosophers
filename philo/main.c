/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 04:39:09 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/17 19:20:49 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		parser(t_data *data, int argc, char **argv);
void	*foo(void *pointer);

static int	start(t_rule *rule, t_philos *philos, int count)
{
	pthread_t	*potok;
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
	while (i < count)
	{
		if (pthread_create(&potok[i], NULL, foo, philos->philo) != 0)
		{
			printf("Error: create\n");
			free(potok);
			return (EXIT_FAILURE);
		}
		philos = philos->next;
		i += 1;
	}
	i = 0;
	while (i < count)
	{
		if (pthread_join(potok[i], NULL))
		{
			free(potok);
			printf("Error: join\n");
			return (EXIT_FAILURE);
		}
		// if (pthread_detach(potok[i], NULL))
		// {
		// 	free(potok);
		// 	printf("Error: join\n");
		// 	return (EXIT_FAILURE);
		// }
		i += 1;
	}
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
