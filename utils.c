/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:29:13 by deddaidi          #+#    #+#             */
/*   Updated: 2025/05/17 15:31:29 by deddaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		signe;

	i = 0;
	signe = 1;
	res = 0;
	if (((str[i] == '-' || str[i] == '+') && str[i + 1]))
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - 48);
		if (res < -2147483648 || res > 2147483647)
			return (0);
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (signe * res);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->die_mutex);
	if (!philo->data->die)
	{
		pthread_mutex_lock(&philo->data->msg);
		printf("%ld  %d %s\n", get_time() - philo->data->time_start, philo->id,
			msg);
		pthread_mutex_unlock(&philo->data->msg);
	}
	pthread_mutex_unlock(&philo->data->die_mutex);
}

void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}

void	destroy_data(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->msg);
	pthread_mutex_destroy(&data->die_mutex);
	pthread_mutex_destroy(&data->last_eat_mutex);
	pthread_mutex_destroy(&data->meals_mutex);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philosophers);
	free(data->forks);
	free(data);
}
