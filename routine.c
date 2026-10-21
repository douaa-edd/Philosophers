/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:28:42 by deddaidi          #+#    #+#             */
/*   Updated: 2025/05/17 15:28:48 by deddaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_forks(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}

void	ft_eating2(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->last_eat_mutex);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->data->last_eat_mutex);
	ft_usleep(philo->data->time_eat);
	pthread_mutex_lock(&philo->data->meals_mutex);
	philo->nb_meals_eat++;
	if (philo->data->nb_time_eat != -1
		&& philo->nb_meals_eat == philo->data->nb_time_eat)
		philo->data->nb_philo_ate++;
	pthread_mutex_unlock(&philo->data->meals_mutex);
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (!philo || !philo->data)
		return (1);
	if (philo->id % 2 == 0)
		usleep(500);
	if (is_dead(philo))
		return (1);
	ft_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	ft_eating2(philo);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	usleep(100);
	return (0);
}

void	ft_sleeping_thinking(t_philo *philo)
{
	long	somme;

	print_msg(philo, "is sleeping");
	ft_usleep(philo->data->time_sleep);
	print_msg(philo, "is thinking");
	somme = philo->data->time_eat + philo->data->time_sleep;
	ft_usleep(philo->data->time_die - somme - 5);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!philo || !philo->data)
		return (NULL);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_eat);
	if (philo->data->nb_philos == 1)
	{
		print_msg(philo, "has taken a fork");
		ft_usleep(philo->data->time_die);
		return (NULL);
	}
	pthread_mutex_lock(&philo->data->last_eat_mutex);
	philo->last_time_eat = get_time();
	pthread_mutex_unlock(&philo->data->last_eat_mutex);
	while (!is_dead(philo))
	{
		if (ft_eating(philo))
			break ;
		ft_sleeping_thinking(philo);
	}
	return (NULL);
}
