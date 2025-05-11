/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoroutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dekravts <dekravts@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:13:09 by dekravts          #+#    #+#             */
/*   Updated: 2025/05/11 21:32:45 by dekravts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->stol->forks_locks[philo->l_fork]);
	print_message(philo, philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->stol->forks_locks[philo->r_fork]);
	print_message(philo, philo->id, "has taken a fork");
	print_message(philo, philo->id, "is eating");
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->philo_lock);
	precise_usleep(philo->stol, philo->stol->e_time);
	if (ded(philo->stol) == 0)
	{
		pthread_mutex_lock(&philo->philo_lock);
		(philo->eat_count)++;
		pthread_mutex_unlock(&philo->philo_lock);
	}
	print_message(philo, philo->id, "is sleeping");
	pthread_mutex_unlock(&philo->stol->forks_locks[philo->l_fork]);
	pthread_mutex_unlock(&philo->stol->forks_locks[philo->r_fork]);
	precise_usleep(philo->stol, philo->stol->s_time);
}

static void	think(t_philo *philo, int silent)
{
	long	think_time;

	pthread_mutex_lock(&philo->philo_lock);
	think_time = (philo->stol->d_time - (get_time() - philo->last_eat)
			- philo->stol->e_time) / 2;
	pthread_mutex_unlock(&philo->philo_lock);
	if (think_time < 0)
		think_time = 0;
	if (think_time > 600)
		think_time = 200;
	if (think_time == 0 && silent == 1)
		think_time = 1;
	if (silent == 0)
		print_message(philo, philo->id, "is thinking");
	precise_usleep(philo->stol, think_time);
}

static void	*one_philo_exception(t_philo *philo)
{
	pthread_mutex_lock(&philo->stol->forks_locks[philo->l_fork]);
	print_message(philo, philo->id, "has taken a fork");
	precise_usleep(philo->stol, philo->stol->d_time);
	print_message(philo, philo->id, "has died");
	pthread_mutex_unlock(&philo->stol->forks_locks[philo->l_fork]);
	return (NULL);
}

void	*philosopher(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->stol->num_m == 0)
		return (NULL);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_eat = philo->stol->start_time;
	pthread_mutex_unlock(&philo->philo_lock);
	delay(philo->stol->start_time);
	if (philo->stol->d_time == 0)
		return (NULL);
	if (philo->stol->num_p == 1)
		return (one_philo_exception);
	else if (philo->id % 2)
		think(philo, 1);
	while (ded(philo->stol) == 0)
	{
		routine(philo);
		think(philo, 0);
	}
	return (NULL);
}
