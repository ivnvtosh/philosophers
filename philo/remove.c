/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:08:26 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/21 17:23:16 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	remove_forks(pthread_mutex_t **forks, int count)
{
	pthread_mutex_t	*temporary;
	int				i;

	if (*forks == NULL)
	{
		return ;
	}
	temporary = *forks;
	*forks = NULL;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&temporary[i]);
		i += 1;
	}
	free(temporary);
}

void	remove_statuses(pthread_mutex_t **statuses, int count)
{
	pthread_mutex_t	*temporary;
	int				i;

	if (*statuses == NULL)
	{
		return ;
	}
	temporary = *statuses;
	*statuses = NULL;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&temporary[i]);
		i += 1;
	}
	free(temporary);
}

void	remove_all(t_data data)
{
	free(data.rule);
	free(data.philos);
	remove_statuses(&data.statuses, data.philos_count);
	remove_forks(&data.forks, data.philos_count);
	free(data.threads);
}
