/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamie <ccamie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 04:39:47 by ccamie            #+#    #+#             */
/*   Updated: 2022/03/29 20:37:22 by ccamie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	long	time;
}	t_rule;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	struct s_rule	*rule;
	long			time_last_eat;
	pthread_mutex_t	status;
}	t_philo;

typedef struct s_philos
{
	struct s_philo	*philo;
	struct s_philos	*next;
}	t_philos;

typedef struct s_forks
{
	pthread_mutex_t	mutex;
	struct s_forks	*next;
}	t_forks;

typedef struct s_data
{
	t_rule		rule;
	int			philo_count;
	t_philos	*philos;
	t_forks		*forks;
}	t_data;

//		my_fork
t_forks		*my_forklast(t_forks *forks);
void		my_forkadd_back(t_forks **forks, t_forks *new);
void		my_forkclear(t_forks **forks);
t_forks		*my_forknew(void);

//		my_philo
t_philos	*my_philolast(t_philos *philos);
void		my_philoadd_back(t_philos **philos, t_philos *new);
void		my_philoclear(t_philos **philos);
t_philos	*my_philonew(int id, t_rule *rule);

//		utils1
size_t		ft_strlen(const char *string);
int			ft_putstr_fd(const char *string, int fd);
int			my_error(const char *string);
int			ft_isdigit(int character);
int			ft_isspace(int character);

//		utils2
int			ft_atoi(const char *string);
long		ft_atol(const char *string);
long		get_time(long time);
long		ft_usleep(long time);

#endif // PHILO_H
