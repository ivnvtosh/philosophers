/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:08:05 by ccamie            #+#    #+#             */
/*   Updated: 2022/04/21 21:10:35 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_rule
{
	int		count_eat;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	long	time_start;
}	t_rule;

typedef struct s_philo
{
	int				id;
	long			time_last_eat;
	int				count_eat;
	t_rule			*rule;
	pthread_mutex_t	*status;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

typedef struct s_data
{
	t_rule			*rule;
	int				philos_count;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_mutex_t	*statuses;
	pthread_mutex_t	*forks;
}	t_data;

void	remove_forks(pthread_mutex_t **forks, int count);
void	remove_statuses(pthread_mutex_t **statuses, int count);
void	remove_philos(t_philo **philos);
void	remove_threads(pthread_t **threads);
void	remove_all(t_data data);

int		ft_isdigit(int character);
int		ft_isspace(int character);
int		ft_atoi(const char *string);
long	ft_atol(const char *string);
size_t	ft_strlen(const char *string);

long	get_time(long time);
void	ft_usleep(long time);

#endif // PHILOSOPHERS_H
