/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:39:17 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/28 16:50:47 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	launch_philosophers(t_data data, t_rule *rule, int i);

void	kill_them(pid_t *process, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		kill(process[i], SIGKILL);
		i += 1;
	}
}

int	launch_process(t_data data)
{
	int	i;

	i = 0;
	while (i < data.philos_count)
	{
		data.process[i] = fork();
		if (data.process[i] == -1)
		{
			kill_them(data.process, i);
			return (-1);
		}
		else if (data.process[i] == 0)
		{
			launch_philosophers(data, data.rule, i);
		}
		else
		{
			i += 1;
		}
	}
	return (0);
}

void	*cheak_die_process(void *pointer)
{
	t_data	data;

	data = *(t_data *)pointer;
	wait(NULL);
	kill_them(data.process, data.philos_count);
	remove_all(data);
	exit(0);
	return (NULL);
}

void	cheak_eat_all(t_data data)
{
	int	i;

	i = 0;
	while (i < data.philos_count)
	{
		sem_wait(data.all_eat);
		i += 1;
	}
}

int	launch(t_data data)
{
	struct timeval	now;
	pthread_t		thread;

	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	data.rule->time_start = now.tv_sec * 1000 + now.tv_usec / 1000;
	if (launch_process(data) == -1)
		return (-1);
	if (pthread_create(&thread, NULL, cheak_die_process, &data) == -1)
	{
		kill_them(data.process, data.philos_count);
		return (-1);
	}
	pthread_detach(thread);
	gettimeofday(&now, NULL);
	while (now.tv_sec * 1000 + now.tv_usec / 1000 - data.rule->time_start < 500)
	{
		gettimeofday(&now, NULL);
		usleep(200);
	}
	cheak_eat_all(data);
	kill_them(data.process, data.philos_count);
	return (0);
}
