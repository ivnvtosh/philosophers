/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:35:49 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/23 19:55:11 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_digit(char **argv);
int	check_for_range_int(char **argv);

static int	get_philo(t_philos **philos, int count, t_rule *rule)
{
	t_philos	*new;
	int			i;

	*philos = NULL;
	i = 1;
	while (i <= count)
	{
		new = my_philonew(i, rule);
		if (new == NULL)
		{
			my_philoclear(philos);
			return (EXIT_FAILURE);
		}
		my_philoadd_back(philos, new);
		i += 1;
	}
	return (EXIT_SUCCESS);
}

static int	get_fork(t_forks **fork, int count)
{
	t_forks	*new;
	int		i;

	*fork = NULL;
	i = 0;
	while (i < count)
	{
		new = my_forknew();
		if (new == NULL)
		{
			my_forkclear(fork);
			return (EXIT_FAILURE);
		}
		my_forkadd_back(fork, new);
		i += 1;
	}
	return (EXIT_SUCCESS);
}

static void	give_a_fork_to_philo(t_forks *forks, t_philos *philos)
{
	t_forks	*prev;

	philos->philo->left = my_forklast(forks)->mutex;
	philos->philo->right = forks->mutex;
	prev = forks;
	forks = forks->next;
	philos = philos->next;
	while (forks != NULL)
	{
		philos->philo->left = prev->mutex;
		philos->philo->right = forks->mutex;
		prev = forks;
		forks = forks->next;
		philos = philos->next;
	}
}

static t_rule	get_game_rule(int argc, char **argv)
{
	t_rule	rule;

	rule.time_die = ft_atoi(argv[1]);
	rule.time_eat = ft_atoi(argv[2]);
	rule.time_sleep = ft_atoi(argv[3]);
	if (argc == 6)
		rule.count_eat = ft_atoi(argv[4]);
	else
		rule.count_eat = -1;
	return (rule);
}

int	parser(t_data *data, int argc, char **argv)
{
	if (check_for_digit(argv))
		return (EXIT_FAILURE);
	if (check_for_range_int(argv))
		return (EXIT_FAILURE);
	data->philo_count = ft_atoi(argv[0]);
	if (data->philo_count > 200)
		return (EXIT_FAILURE);
	data->rule = get_game_rule(argc, argv);
	if (get_fork(&data->forks, data->philo_count))
		return (EXIT_FAILURE);
	if (get_philo(&data->philos, data->philo_count, &data->rule))
	{
		my_forkclear(&data->forks);
		return (EXIT_FAILURE);
	}
	give_a_fork_to_philo(data->forks, data->philos);
	return (EXIT_SUCCESS);
}
