/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:08:01 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/28 16:26:37 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int				check_for_digit(int count, char **parameters);
int				check_for_range_int(int count, char **parameters);

t_rule			*get_rule(int count, char **parameters);
t_philo			*get_philos(int count, t_rule *rule);
pid_t			*get_process(int count);

int	sem_open_all(t_data *data)
{
	data->forks = sem_open("philoFork", O_CREAT, 777, data->philos_count);
	if (data->forks == NULL)
		return (-1);
	data->print = sem_open("philoPrint", O_CREAT, 777, 1);
	if (data->print == NULL)
		return (-1);
	data->all_eat = sem_open("philoAllEat", O_CREAT, 777, data->philos_count);
	if (data->all_eat == NULL)
		return (-1);
	return (0);
}

void	give_a_forks_to_philo(t_philo *philos, int count, t_data data)
{
	int	i;

	i = 0;
	while (i < count)
	{
		philos[i].forks = data.forks;
		philos[i].print = data.print;
		philos[i].all_eat = data.all_eat;
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
	data->philos = get_philos(data->philos_count, data->rule);
	if (data->philos == NULL)
		return (-1);
	data->process = get_process(data->philos_count);
	if (data->process == NULL)
		return (-1);
	if (sem_open_all(data) == -1)
		return (-1);
	give_a_forks_to_philo(data->philos, data->philos_count, *data);
	return (0);
}
