/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dekravts <dekravts@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:45:56 by dekravts          #+#    #+#             */
/*   Updated: 2025/04/29 06:49:09 by dekravts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_ded(t_stol *stol, int state)
{
	pthread_mutex_lock(&stol->dead_lock);
	stol->dead_flag = state;
	pthread_mutex_unlock(&stol->dead_lock);
}

int	ded(t_stol *stol)
{
	int	ded;

	ded = 0;
	pthread_mutex_lock(&stol->dead_lock);
	if (stol->dead_flag == 1)
		ded = 1;
	pthread_mutex_unlock(&stol->dead_lock);
	return (ded);
}

static int	stop(t_philo *philo)
{
	long	time;

	time = get_time();
	if ((time - philo->last_eat) >= philo->stol->d_time)
	{
		print_message(philo, philo->id, "\x1b[31mhas died\x1b[0m");
		set_ded(philo->stol, 1);
		pthread_mutex_unlock(&philo->philo_lock);
		return (1);
	}
	return (0);
}

static int	has_finished(t_stol *stol)
{
	int	i;
	int	all_ate;

	all_ate = 1;
	i = 0;
	while (i < stol->num_p)
	{
		pthread_mutex_lock(&stol->philos[i]->philo_lock);
		if (stop(stol->philos[i]))
			return (1);
		if (stol->num_m != -1)
			if (stol->philos[i]->eat_count
				< stol->num_m)
				all_ate = 0;
		pthread_mutex_unlock(&stol->philos[i]->philo_lock);
		i++;
	}
	if (stol->num_m != -1 && all_ate == 1)
	{
		printf("\x1b[32mEveryone had their food, stop here\x1b[0m\n");
		set_ded(stol, 1);
		return (1);
	}
	return (0);
}

void	*monitor(void *data)
{
	t_stol	*stol;

	stol = (t_stol *)data;
	if (stol->num_m == 0)
		return (NULL);
	set_ded(stol, 0);
	delay(stol->start_time);
	while (1)
	{
		if (has_finished(stol) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
