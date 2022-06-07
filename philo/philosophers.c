/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:08:03 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/28 14:23:45 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parser(t_data *data, int count, char **parameters);
int	launch(t_data data);

int	philosophers(int count, char **parameters)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (parser(&data, count, parameters) != 0)
	{
		remove_all(data);
		write(2, "Error\n", 6);
		return (EXIT_FAILURE);
	}
	if (launch(data) != 0)
	{
		remove_all(data);
		write(2, "Error\n", 6);
		return (EXIT_FAILURE);
	}
	else
	{
		remove_all(data);
		return (EXIT_SUCCESS);
	}
}
