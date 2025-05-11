/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dekravts <dekravts@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:07:44 by dekravts          #+#    #+#             */
/*   Updated: 2025/05/11 21:32:39 by dekravts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*cleanup(t_stol *stol)
{
	int	i;

	if (!stol)
		return (NULL);
	if (stol->forks_locks != NULL)
		free(stol->forks_locks);
	if (stol->philos != NULL)
	{
		i = 0;
		while (i < stol->num_p)
		{
			if (stol->philos[i] != NULL)
				free(stol->philos[i]);
			i++;
		}
		free(stol->philos);
	}
	free(stol);
	return (NULL);
}

void	destroy_mutex(t_stol *stol)
{
	int	i;

	i = 0;
	while (i < stol->num_p)
	{
		pthread_mutex_destroy(&stol->forks_locks[i]);
		pthread_mutex_destroy(&stol->philos[i]->philo_lock);
		i++;
	}
	pthread_mutex_destroy(&stol->print_lock);
	pthread_mutex_destroy(&stol->dead_lock);
}
