/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:07:57 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/08 19:38:59 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philosophers(int count, char **parameters);

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		return (philosophers(--argc, ++argv));
	}
	else
	{
		write(2, "Error\n", 6);
		return (EXIT_FAILURE);
	}
}
