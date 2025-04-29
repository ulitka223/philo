/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dekravts <dekravts@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:50:52 by dekravts          #+#    #+#             */
/*   Updated: 2025/04/29 07:17:30 by dekravts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_stol	t_stol;

typedef struct s_stol
{
	int				num_p;
	long			start_time;
	long			d_time;
	long			e_time;
	long			s_time;
	int				num_m;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks_locks;
	pthread_t		monitor_thread;
	t_philo			**philos;
}	t_stol;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	philo_lock;
	int				id;
	int				eat_count;
	int				l_fork;
	int				r_fork;
	long			last_eat;
	t_stol			*stol;
}	t_philo;

void		*monitor(void *data);
int			ded(t_stol *stol);
void		*philosopher(void *phil);
long		get_time(void);
void		delay(long start_time);
void		precise_usleep(t_stol *stol, long sleep_time);
t_stol		*init(int argc, char **argv, int i);
void		print_message(t_philo *philo, int id, char *message);
int			ft_atoi(char *str);
void		destroy_mutex(t_stol *stol);
void		*cleanup(t_stol *stol);
int			validate_args(t_stol *stol);

#endif