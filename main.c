/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dekravts <dekravts@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:53:19 by dekravts          #+#    #+#             */
/*   Updated: 2025/05/11 21:32:31 by dekravts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define USAGE "number, die_time, eat_time, sleep_time [number of meals]\x1b[0m"


static void	threads_init(t_stol *stol)
{
	int	i;

	i = 0;
	stol->start_time = get_time();
	while (i < stol->num_p)
	{
		pthread_mutex_lock(&stol->philos[i]->philo_lock);
		stol->philos[i]->last_eat = stol->start_time;
		pthread_mutex_unlock(&stol->philos[i]->philo_lock);
		pthread_create(&stol->philos[i]->thread, NULL, &philosopher,
			stol->philos[i]);
		i++;
	}
	pthread_create(&stol->monitor_thread, NULL,
		&monitor, stol);
	return ;
}

static void	stoping(t_stol *stol)
{
	int	i;

	i = 0;
	while (i < stol->num_p)
	{
		pthread_join(stol->philos[i]->thread, NULL);
		i++;
	}
	pthread_join(stol->monitor_thread, NULL);
	destroy_mutex(stol);
	cleanup(stol);
}

int	main(int argc, char **argv)
{
	t_stol	*stol;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of argumnets, Usage : \x1b[35m%s\n", USAGE);
		return (1);
	}
	stol = NULL;
	stol = init(argc, argv, 1);
	if (!stol)
		return (1);
	threads_init(stol);
	stoping(stol);
	return (0);
}
