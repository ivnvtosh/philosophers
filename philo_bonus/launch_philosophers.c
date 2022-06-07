/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:45:25 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/28 16:49:14 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*the_life_of_a_philosopher_1(void *pointer);
void	*the_life_of_a_philosopher_2(void *pointer);
int		check_die(t_philo *philo);

char	*create_name_semaphore_for_philo(int i)
{
	char	*sem_status;
	char	*temporary;

	temporary = ft_itoa(i);
	if (temporary == NULL)
		exit(EXIT_FAILURE);
	sem_status = ft_strjoin("philostatus", temporary);
	if (sem_status == NULL)
		exit(EXIT_FAILURE);
	free(temporary);
	return (sem_status);
}

void	create_sem_status_for_philo(t_philo *philo, char *sem_status)
{
	sem_unlink(sem_status);
	philo->status = sem_open(sem_status, O_CREAT, 777, 1);
	if (philo->status == SEM_FAILED)
	{
		exit(EXIT_FAILURE);
	}
}

void	launch_thread(t_philo *philo, int count, int i)
{
	pthread_t	thread;

	if (i < count / 2)
	{
		if (pthread_create(&thread, NULL, \
			the_life_of_a_philosopher_2, philo) != 0)
		{
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (pthread_create(&thread, NULL, \
			the_life_of_a_philosopher_1, philo) != 0)
		{
			exit(EXIT_FAILURE);
		}
	}
	pthread_detach(thread);
}

void	wait_lauch_all(t_rule *rule)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	while (now.tv_sec * 1000 + now.tv_usec / 1000 - rule->time_start < 500)
	{
		gettimeofday(&now, NULL);
		usleep(200);
	}
	rule->time_start = now.tv_sec * 1000 + now.tv_usec / 1000;
}

void	launch_philosophers(t_data data, t_rule *rule, int i)
{
	char	*sem_status;
	int		status;

	sem_wait(data.all_eat);
	sem_status = create_name_semaphore_for_philo(i);
	create_sem_status_for_philo(&data.philos[i], sem_status);
	launch_thread(&data.philos[i], data.philos_count, i);
	wait_lauch_all(rule);
	status = check_die(&data.philos[i]);
	sem_close(data.philos[i].status);
	sem_unlink(sem_status);
	free(sem_status);
	exit(status);
}
