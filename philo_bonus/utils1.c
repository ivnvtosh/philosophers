/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:08:07 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/08 18:08:08 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int character)
{
	return (character >= 48 && character <= 57);
}

int	ft_isspace(int character)
{
	return ((character >= 9 && character <= 13) || character == 32);
}

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

size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
		i += 1;
	return (i);
}
