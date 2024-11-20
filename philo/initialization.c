/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:47:37 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/11/19 21:47:39 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cheack_max_int(long i)
{
	if (i > __INT_MAX__)
		print_error("eroore");
}

void	parsing_argc(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	data->num_times_to_eat = -1;
	while (i < ac)
	{
		if (i == 1)
			data->num_philos = ft_atoi(av[1]);
		else if (i == 2)
			data->time_to_die = ft_atoi(av[2]);
		else if (i == 3)
			data->time_to_eat = ft_atoi(av[3]);
		else if (i == 4)
			data->time_to_sleep = ft_atoi(av[4]);
		else if (i == 5)
			data->num_times_to_eat = ft_atoi(av[5]);
		cheack_max_int(ft_atoi(av[i]));
		i++;
	}
}

void	initial_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		data->philo[i++].right_fork = (pthread_mutex_t *)
			malloc(sizeof(pthread_mutex_t));
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(data->philo[i].right_fork, NULL);
		if (i == 0 && data->num_philos != 1)
			data->philo[i].left_fork = data->philo[data->num_philos
				- 1].right_fork;
		else if (data->num_philos != 1)
			data->philo[i].left_fork = data->philo[i - 1].right_fork;
		data->philo[i].data_p = data;
		data->philo[i].id = i + 1;
		pthread_mutex_init(&data->philo[i].cheack_deid, NULL);
		pthread_mutex_init(&data->philo[i].meals_mutex, NULL);
		pthread_mutex_init(&data->philo[i].cheack_num_eat_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meal_time_mutex, NULL);
	pthread_mutex_init(&data->check_death, NULL);
}

void	thread_create(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = current_time();
	while (i < data->num_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]);
		i++;
	}
	cheack_philo_died(data);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

void	initial_data(int ac, char **av, t_data *data)
{
	int	nb;

	nb = 0;
	parsing_argc(ac, av, data);
	data->philo = (t_philo *)malloc((data->num_philos) * sizeof(t_philo));
	if (data->philo == NULL)
	{
		print_error("malloc failed");
		return ;
	}
	memset(data->philo, 0, sizeof(t_philo) * data->num_philos);
	data->is_dead = false;
	data->is_errore = false;
	nb = 0;
	if (data->time_to_die < data->time_to_eat)
		data->time_to_eat = data->time_to_die + 1;
	while (data->num_philos > nb)
	{
		data->philo[nb].last_meal_time = current_time();
		nb++;
	}
	initial_forks(data);
	thread_create(data);
}
