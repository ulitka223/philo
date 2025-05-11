/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dekravts <dekravts@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:21:14 by dekravts          #+#    #+#             */
/*   Updated: 2025/05/11 21:32:36 by dekravts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static pthread_mutex_t	*init_forks(t_stol *stol)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * stol->num_p);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < stol->num_p)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

static void	take_forks(t_philo *philo)
{
	philo->l_fork = philo->id;
	philo->r_fork = (philo->id + 1) % philo->stol->num_p;
	if (philo->id % 2)
	{
		philo->l_fork = (philo->id + 1) % philo->stol->num_p;
		philo->r_fork = philo->id;
	}
}

static t_philo	**init_philo(t_stol *stol)
{
	t_philo		**philos;
	int			i;

	philos = malloc(sizeof(t_philo) * stol->num_p);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < stol->num_p)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		if (pthread_mutex_init(&philos[i]->philo_lock, 0) != 0)
			return (NULL);
		philos[i]->stol = stol;
		philos[i]->id = i;
		philos[i]->eat_count = 0;
		take_forks(philos[i]);
		i++;
	}
	return (philos);
}

static int	mutex_init(t_stol *stol)
{
	stol->forks_locks = init_forks(stol);
	if (!stol->forks_locks)
		return (0);
	if (pthread_mutex_init(&stol->dead_lock, 0) != 0)
		return (0);
	if (pthread_mutex_init(&stol->print_lock, 0) != 0)
		return (0);
	return (1);
}

t_stol	*init(int argc, char **argv, int i)
{
	t_stol	*stol;

	stol = malloc(sizeof(t_stol));
	if (!stol)
		return (NULL);
	stol->num_p = ft_atoi(argv[i++]);
	stol->d_time = ft_atoi(argv[i++]);
	stol->e_time = ft_atoi(argv[i++]);
	stol->s_time = ft_atoi(argv[i++]);
	stol->num_m = -1;
	if (argc == 6)
		stol->num_m = ft_atoi(argv[i++]);
	stol->philos = init_philo(stol);
	if (!stol->philos)
		return (NULL);
	if (!mutex_init(stol))
		return (NULL);
	if (!validate_args(stol))
		return (NULL);
	stol->dead_flag = 0;
	return (stol);
}
