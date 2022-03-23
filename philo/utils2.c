/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:13:49 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/19 21:41:32 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *string)
{
	int	number;
	int	sign;

	sign = 1;
	while (ft_isspace(*string))
		string += 1;
	if (*string == 43 || *string == 45)
		if (*string++ == 45)
			sign = -1;
	number = 0;
	while (ft_isdigit(*string))
		number = number * 10 + *string++ - 48;
	return (number * sign);
}

long	ft_atol(const char *string)
{
	long	number;
	long	sign;

	sign = 1;
	while (ft_isspace(*string))
		string += 1;
	if (*string == 43 || *string == 45)
		if (*string++ == 45)
			sign = -1;
	number = 0;
	while (ft_isdigit(*string))
	{
		if (number < -__INT_MAX__ - 1 || number > __INT_MAX__)
			return (__LONG_MAX__);
		number = number * 10 + *string++ - 48;
	}
	return (number * sign);
}

long	get_time(long time)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	return (now.tv_sec * 1000 + now.tv_usec / 1000) - time;
}
