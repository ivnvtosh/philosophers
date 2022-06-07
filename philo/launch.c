/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:39:17 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/21 17:33:06 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*the_life_of_a_philosopher_1(void *pointer);
void	*the_life_of_a_philosopher_2(void *pointer);

void	detach_threads(pthread_t *threads, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_detach(threads[i]);
		i += 1;
	}
}

int	launch_thread_one(t_data data, int i, void *(*func)(void *))
{
	if (pthread_create(&data.threads[i], NULL, func, &data.philos[i]) != 0)
	{
		detach_threads(data.threads, i - 1);
		return (-1);
	}
	return (0);
}

int	launch_threads(t_data data, t_rule *rule)
{
	struct timeval	now;
	int				i;

	i = 0;
	while (i < data.philos_count)
	{
		if (i % 2 == 0)
		{
			if (launch_thread_one(data, i++, the_life_of_a_philosopher_1))
				return (-1);
		}
		else
		{
			if (launch_thread_one(data, i++, the_life_of_a_philosopher_2))
				return (-1);
		}
	}
	gettimeofday(&now, NULL);
	while (now.tv_sec * 1000 + now.tv_usec / 1000 - rule->time_start < 100)
	{
		gettimeofday(&now, NULL);
		usleep(200);
	}
	rule->time_start = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (0);
}

void	check_die(t_data data);

int	launch(t_data data)
{
	struct timeval	time_start;

	if (gettimeofday(&time_start, NULL) == -1)
		return (-1);
	data.rule->time_start = time_start.tv_sec * 1000 + \
		time_start.tv_usec / 1000;
	if (launch_threads(data, data.rule) == -1)
		return (-1);
	detach_threads(data.threads, data.philos_count);
	check_die(data);
	return (0);
}
