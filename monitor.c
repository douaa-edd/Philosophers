/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:29:25 by deddaidi          #+#    #+#             */
/*   Updated: 2025/05/17 15:30:48 by deddaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->die_mutex);
	dead = philo->data->die;
	pthread_mutex_unlock(&philo->data->die_mutex);
	return (dead);
}

void	death_checker(t_philo *philo, int i)
{
	long	now;
	long	last;

	pthread_mutex_lock(&philo->data->last_eat_mutex);
	now = get_time();
	last = philo[i].last_time_eat;
	pthread_mutex_unlock(&philo->data->last_eat_mutex);
	if (now - last > philo->data->time_die)
	{
		pthread_mutex_lock(&philo->data->die_mutex);
		if (!philo->data->die)
		{
			philo->data->die = 1;
			pthread_mutex_lock(&philo->data->msg);
			printf("%ld  %d died\n", now - philo->data->time_start,
				philo[i].id);
			pthread_mutex_unlock(&philo->data->msg);
		}
		pthread_mutex_unlock(&philo->data->die_mutex);
	}
}

void	meals_checker(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meals_mutex);
	if (philo->data->nb_time_eat != -1
		&& philo->data->nb_philo_ate >= philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo->data->die_mutex);
		philo->data->die = 1;
		pthread_mutex_unlock(&philo->data->die_mutex);
	}
	pthread_mutex_unlock(&philo->data->meals_mutex);
}

void	*ft_monitor(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	if (!philo || !philo->data)
		return (NULL);
	while (!is_dead(philo))
	{
		i = 0;
		while (i < philo->data->nb_philos && !is_dead(philo))
		{
			death_checker(philo, i);
			if (is_dead(philo))
				break ;
			meals_checker(philo);
			usleep(500);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
