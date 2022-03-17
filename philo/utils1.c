/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:59:26 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/15 18:47:21 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
		i += 1;
	return (i);
}

int	ft_putstr_fd(const char *string, int fd)
{
	size_t	i;
	ssize_t	n;

	i = ft_strlen(string);
	n = write(fd, string, i);
	if (n == EOF || (size_t)n != i)
	{
		return (EOF);
	}
	else
	{
		return (n);
	}
}

int	my_error(const char *string)
{
	ft_putstr_fd(string, 2);
	return (EXIT_FAILURE);
}

int	ft_isdigit(int character)
{
	return (character >= 48 && character <= 57);
}

int	ft_isspace(int character)
{
	return ((character >= 9 && character <= 13) || character == 32);
}
