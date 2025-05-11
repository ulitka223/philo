/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dekravts <dekravts@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:10:54 by dekravts          #+#    #+#             */
/*   Updated: 2025/05/11 21:32:49 by dekravts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	delay(long start_time)
{
	while (get_time() < start_time)
		continue ;
}

void	precise_usleep(t_stol *stol, long sleep_time)
{
	long	woke;

	woke = get_time() + sleep_time;
	while (get_time() < woke)
	{
		if (ded(stol))
			break ;
		usleep(80);
	}
}
