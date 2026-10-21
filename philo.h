/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:29:42 by deddaidi          #+#    #+#             */
/*   Updated: 2025/05/17 15:29:44 by deddaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				nb_time_eat;
	long			time_start;
	int				nb_philo_ate;
	int				die;
	pthread_mutex_t	msg;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	*forks;
	pthread_t		*philosophers;
	pthread_t		monitor;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	long			last_time_eat;
	int				nb_meals_eat;

}					t_philo;

long				ft_atoi(const char *str);
long				get_time(void);
int					data_init(t_data *data, int ac, char **av);
int					mutex_init(t_data *data);
void				philo_init(t_data *data, t_philo *philos);
void				ft_simulation(t_data *data, t_philo *philos);
void				*ft_routine(void *arg);
long				get_time(void);
void				print_msg(t_philo *philo, char *msg);
void				ft_usleep(long time);
void				*ft_monitor(void *arg);
void				destroy_data(t_data *data);
int					is_dead(t_philo *philo);
#endif
