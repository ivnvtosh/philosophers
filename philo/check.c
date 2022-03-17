/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:23:41 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/15 18:56:24 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_for_digit(char **argv)
{
	int	i;
	int	j;

	j = 0;
	while (argv[j])
	{
		i = 0;
		if (argv[j][i] == '-')
			i += 1;
		if (argv[j][i] == '\0')
			return (EXIT_FAILURE);
		while (ft_isdigit(argv[j][i]))
			i += 1;
		if (argv[j][i] != '\0')
			return (EXIT_FAILURE);
		j += 1;
	}
	return (EXIT_SUCCESS);
}

int	check_for_range_int(char **argv)
{
	long	n;
	int		i;

	i = 0;
	while (argv[i])
	{
		n = atol(argv[i]);
		if (n <= 0 || n > __INT_MAX__)
			return (EXIT_FAILURE);
		i += 1;
	}
	return (EXIT_SUCCESS);
}
