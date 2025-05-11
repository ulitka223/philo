/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dekravts <dekravts@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:14:38 by dekravts          #+#    #+#             */
/*   Updated: 2025/05/11 21:32:52 by dekravts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


#define MSG \
"\x1b[33mCan you even have a negative amount of people or time?\x1b[0m\n"

#define ERR "Args Should Have Numeric Value"

int	ft_atoi(char *str)
{
	int	i;
	int	result;
	int	sign;

	i = -1;
	result = 0;
	sign = 1;
	while (str[++i])
		if (((str[i] < 9 || str[i] > 13) || (str[i] != 32)) \
			&& (str[i] != 43 && str[i] != 45) && (str[i] < 48 || str[i] > 57))
			return (printf("\x1b[31m%s\x1b[0m\n", ERR), -1);
	i = -1;
	while ((str[++i] >= 9 && str[i] <= 13) || (str[i] == 32))
		;
	if (str[i] == 45)
		return (printf("%s", MSG), -1);
	if (str[i] == 43)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	validate_args(t_stol *stol)
{
	if (stol->d_time < 0)
		return (0);
	if (stol->e_time < 0)
		return (0);
	if (stol->s_time < 0)
		return (0);
	return (1);
}

void	print_message(t_philo *philo, int id, char *message)
{
	pthread_mutex_lock(&philo->stol->dead_lock);
	if (philo->stol->dead_flag)
		return ((void)pthread_mutex_unlock(&philo->stol->dead_lock));
	pthread_mutex_lock(&philo->stol->print_lock);
	printf("%ld %d %s\n", get_time() - philo->stol->start_time,
		id + 1, message);
	pthread_mutex_unlock(&philo->stol->print_lock);
	pthread_mutex_unlock(&philo->stol->dead_lock);
}
