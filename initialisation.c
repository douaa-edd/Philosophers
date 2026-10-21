/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:29:00 by deddaidi          #+#    #+#             */
/*   Updated: 2025/05/17 15:32:12 by deddaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(t_data *data, int ac, char **av)
{
	data->nb_philos = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->nb_time_eat = ft_atoi(av[5]);
		if (data->nb_time_eat < 1)
			return (1);
	}
	else
		data->nb_time_eat = -1;
	if (data->nb_philos < 1 || data->time_die < 1 || data->time_eat < 1
		|| data->time_sleep < 1)
		return (1);
	data->time_start = get_time();
	data->nb_philo_ate = 0;
	data->die = 0;
	data->forks = NULL;
	return (0);
}

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (1);
	data->philosophers = malloc(sizeof(pthread_t) * data->nb_philos);
	if (!data->philosophers)
	{
		free(data->forks);
		return (1);
	}
	pthread_mutex_init(&data->msg, NULL);
	pthread_mutex_init(&data->die_mutex, NULL);
	pthread_mutex_init(&data->last_eat_mutex, NULL);
	pthread_mutex_init(&data->meals_mutex, NULL);
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

void	philo_init(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].nb_meals_eat = 0;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		philos[i].last_time_eat = get_time();
		i++;
	}
}

void	ft_simulation(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	data->time_start = get_time();
	while (i < data->nb_philos)
	{
		pthread_create(&data->philosophers[i], NULL, ft_routine, &philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, ft_monitor, philos);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philosophers[i], NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}
