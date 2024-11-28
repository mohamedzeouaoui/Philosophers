/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_healpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:48:34 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/11/19 21:48:36 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_1philo(t_philo *philo)
{
	if (philo->data_p->num_philos == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_lock_print("take a right fork", philo);
		ft_usleep(philo->data_p->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
	}
	return ;
}

int	func_25_check_deid(t_data *data, int *i, int *ll)
{
	pthread_mutex_lock(&data->philo[*i].cheack_deid);
	if (current_time() - data->philo[*i].last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->check_death);
		ft_print_deid(data, *i);
		pthread_mutex_lock(&data->died_mutex);

		data->is_dead = true;
		pthread_mutex_unlock(&data->died_mutex);

		data->is_errore = true;
		pthread_mutex_unlock(&data->check_death);
		pthread_mutex_unlock(&data->philo[*i].cheack_deid);
		return (-1);
	}
	pthread_mutex_unlock(&data->philo[*i].cheack_deid);
	pthread_mutex_lock(&data->philo[*i].cheack_num_eat_mutex);
	if (data->philo[*i].meals_eaten == data->num_times_to_eat
		&& data->num_times_to_eat != -1)
	{
		data->philo[*i].meals_eaten = data->num_times_to_eat + 1;
		(*ll)++;
	}
	pthread_mutex_lock(&data->check_death);
	if (*ll == data->num_philos)
	{
		pthread_mutex_lock(&data->died_mutex);
		data->is_dead = true;
		pthread_mutex_unlock(&data->died_mutex);
		return (-1);
		

	}
	pthread_mutex_unlock(&data->check_death);
	pthread_mutex_unlock(&data->philo[*i].cheack_num_eat_mutex);
	return (0);
}

void	*cheack_philo_died(void *ptr)
{
	int		i;
	t_data	*data;
	int		ll;

	ll = 0;
	data = (t_data *)ptr;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (func_25_check_deid(data, &i, &ll) == -1)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

void	update_last_meal_time(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->cheack_deid);
	philosopher->last_meal_time = current_time();
	pthread_mutex_unlock(&philosopher->cheack_deid);
}

long	time_to_print(t_philo *philo)
{
	return ((current_time() - philo->data_p->start_time));
}
