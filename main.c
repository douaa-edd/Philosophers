/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:28:29 by deddaidi          #+#    #+#             */
/*   Updated: 2025/05/17 15:28:31 by deddaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*data_alloc(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (data_init(data, ac, av))
	{
		free(data);
		printf("Error : Arguments should be a number greater than 0\n");
		return (NULL);
	}
	return (data);
}

void	*philos_alloc(t_data *data)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!philos)
	{
		free(data);
		return (NULL);
	}
	return (philos);
}

int	error_msg(void)
{
	printf("Usage: ./philo number_of_philosophers \
	time_to_die time_to_eat time_to_sleep \
    [number_of_times_each_philosopher_must_eat]\n");
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philos;

	if (ac == 5 || ac == 6)
	{
		data = data_alloc(ac, av);
		if (!data)
			return (1);
		philos = philos_alloc(data);
		if (!philos)
			return (1);
		if (mutex_init(data))
		{
			free(data);
			free(philos);
			return (1);
		}
		philo_init(data, philos);
		ft_simulation(data, philos);
	}
	else
		return (error_msg());
	destroy_data(data);
	free(philos);
	return (0);
}
