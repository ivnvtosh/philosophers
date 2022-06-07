/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:02:10 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/26 21:02:58 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_strcpy(char *from, char *in)
{
	size_t	i;

	i = 0;
	while (from[i] != '\0')
	{
		in[i] = from[i];
		i += 1;
	}
	in[i] = '\0';
}

char	*ft_strdup(char *string)
{
	char	*duplicate;

	duplicate = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
	if (duplicate == NULL)
		return (NULL);
	ft_strcpy(string, duplicate);
	return (duplicate);
}

char	*ft_strjoin(char *one, char *two)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = ft_strlen(one);
	j = ft_strlen(two);
	new = (char *)malloc(sizeof(char) * (i + j + 1));
	if (new == NULL)
		return (NULL);
	ft_strcpy(one, new);
	ft_strcpy(two, new + i);
	new[i + j] = '\0';
	return (new);
}

static size_t	nbrlen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	if (n < 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		n /= 10;
		len += 1;
	}
	return (len);
}

char	*ft_itoa(int num)
{
	char	*s;
	int		slen;

	if (num == -2147483648)
		return (ft_strdup("-2147483648"));
	slen = nbrlen(num);
	s = (char *)malloc(sizeof(*s) * (slen + 1));
	if (s == NULL)
		return (NULL);
	s[slen--] = 0;
	if (num == 0)
		s[0] = 48;
	if (num < 0)
	{
		s[0] = 45;
		num = -num;
	}
	while (num)
	{
		s[slen--] = num % 10 + 48;
		num /= 10;
	}
	return (s);
}
