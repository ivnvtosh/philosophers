/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:28:44 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/23 18:05:46 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_forks	*my_forklast(t_forks *forks)
{
	while (forks->next != NULL)
		forks = forks->next;
	return (forks);
}

void	my_forkadd_back(t_forks **forks, t_forks *new)
{
	if (*forks == NULL)
		*forks = new;
	else
		my_forklast(*forks)->next = new;
}

void	my_forkclear(t_forks **forks)
{
	t_forks	*prev;
	t_forks	*elem;

	elem = *forks;
	*forks = NULL;
	while (elem != NULL)
	{
		prev = elem;
		elem = elem->next;
		pthread_mutex_destroy(&prev->mutex);		//	wtf!!!!
		free(prev);
	}
}

t_forks	*my_forknew(void)
{
	t_forks	*forks;

	forks = (t_forks *)malloc(sizeof(t_forks));
	if (forks == NULL)
		return (NULL);
	if (pthread_mutex_init(&forks->mutex, NULL) != 0)
	{
		free(forks);
		return (NULL);
	}
	forks->next = NULL;
	return (forks);
}
