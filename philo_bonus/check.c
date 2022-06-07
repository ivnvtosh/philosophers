/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:07:55 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/08 18:07:56 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_for_digit(int count, char **parameters)
{
	int	i;
	int	j;

	j = 0;
	while (j < count)
	{
		i = 0;
		if (parameters[j][i] == '-')
			i += 1;
		if (parameters[j][i] == '\0')
			return (-1);
		while (ft_isdigit(parameters[j][i]))
			i += 1;
		if (parameters[j][i] != '\0')
			return (-1);
		j += 1;
	}
	return (0);
}

int	check_for_range_int(int count, char **parameters)
{
	long	n;
	int		j;

	j = 0;
	while (j < count)
	{
		n = ft_atol(parameters[j]);
		if (n == __LONG_MAX__)
			return (-1);
		j += 1;
	}
	return (0);
}
