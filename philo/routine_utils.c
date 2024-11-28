/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:54:15 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/11/20 22:25:10 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_deid(t_data *data, int i)
{
	pthread_mutex_lock(&data->write_lock);
	printf("%ld philosopher %d has died\n", current_time() - data->start_time,
		data->philo[i].id);
	pthread_mutex_unlock(&data->write_lock);
}

void	ft_lock_print(char *str, t_philo *p)
{
	long	nb;

	pthread_mutex_lock(&p->data_p->write_lock);
	pthread_mutex_lock(&p->data_p->died_mutex);
	if (!p->data_p->is_dead)
	{
		pthread_mutex_unlock(&p->data_p->died_mutex);
		nb = (current_time() - p->data_p->start_time);
		printf("%ld %d %s\n", nb, p->id, str);
	}
	else
		pthread_mutex_unlock(&p->data_p->died_mutex);

	pthread_mutex_unlock(&p->data_p->write_lock);
}

void	eating_pair(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_lock_print("take a right fork", philo);
	pthread_mutex_lock(philo->left_fork);
	ft_lock_print("take a left fork", philo);
	ft_lock_print("is eating", philo);
	update_last_meal_time(philo);
	ft_usleep(philo->data_p->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	eating_inpair(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_lock_print("take a left fork", philo);
	pthread_mutex_lock(philo->right_fork);
	ft_lock_print("take a right fork", philo);
	ft_lock_print("is eating", philo);
	update_last_meal_time(philo);
	ft_usleep(philo->data_p->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
