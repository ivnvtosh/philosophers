/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:08:01 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/28 15:37:28 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				check_for_digit(int count, char **parameters);
int				check_for_range_int(int count, char **parameters);

t_rule			*get_rule(int count, char **parameters);
pthread_mutex_t	*get_forks(int count);
pthread_mutex_t	*get_statuses(int count);
t_philo			*get_philos(int count, t_rule *rule);
pthread_t		*get_threads(int count);

void	give_a_fork_to_philo(pthread_mutex_t *forks, t_philo *philos, int count)
{
	int	i;

	if (count == 1)
	{
		philos[0].left = &forks[0];
		philos[0].right = &forks[0];
		return ;
	}
	philos[0].left = &forks[0];
	philos[0].right = &forks[count - 1];
	count -= 1;
	i = 1;
	while (i < count)
	{
		philos[i].left = &forks[i];
		philos[i].right = &forks[i - 1];
		i += 1;
	}
	philos[count].left = &forks[count];
	philos[count].right = &forks[count - 1];
}

void	give_a_status_to_philo(pthread_mutex_t *statuses, \
t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		philos[i].status = &statuses[i];
		i += 1;
	}
}

int	parser(t_data *data, int count, char **parameters)
{
	if (check_for_digit(count, parameters) == -1)
		return (-1);
	if (check_for_range_int(count, parameters) == -1)
		return (-1);
	data->rule = get_rule(count, parameters);
	if (data->rule == NULL)
		return (-1);
	data->philos_count = ft_atoi(parameters[0]);
	if (data->philos_count <= 0)
		return (-1);
	data->forks = get_forks(data->philos_count);
	if (data->forks == NULL)
		return (-1);
	data->statuses = get_statuses(data->philos_count);
	if (data->statuses == NULL)
		return (-1);
	data->philos = get_philos(data->philos_count, data->rule);
	if (data->philos == NULL)
		return (-1);
	data->threads = get_threads(data->philos_count);
	if (data->threads == NULL)
		return (-1);
	give_a_fork_to_philo(data->forks, data->philos, data->philos_count);
	give_a_status_to_philo(data->statuses, data->philos, data->philos_count);
	return (0);
}
