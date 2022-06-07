/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:08:26 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/28 16:36:02 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	remove_all(t_data data)
{
	free(data.rule);
	free(data.philos);
	free(data.process);
	sem_unlink("philoFork");
	sem_unlink("philoPrint");
	sem_unlink("philoAllEat");
}
