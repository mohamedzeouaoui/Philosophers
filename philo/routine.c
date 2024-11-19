/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:54:15 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/11/19 21:54:17 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lock_print(char *str, t_philo *p)
{
	long	nb;

	pthread_mutex_lock(&p->data_p->write_lock);
	if (!p->data_p->is_dead)
	{
		nb = (current_time() - p->data_p->start_time);
		printf("%ld %d %s\n", nb, p->id, str);
	}
	pthread_mutex_unlock(&p->data_p->write_lock);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_p->check_death);
	if (philo->id % 2 == 0 && !philo->data_p->is_dead)
	{
		pthread_mutex_unlock(&philo->data_p->check_death);
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
	if (philo->id % 2 == 1 && !philo->data_p->is_dead)
	{
		pthread_mutex_unlock(&philo->data_p->check_death);
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
	philo->meals_eaten = philo->meals_eaten + 1;
}

void	thinking(t_philo *philo)
{
	if (!philo->data_p->is_dead)
	{
		ft_lock_print("is thinking", philo);
	}
}

void	sleping(t_philo *philo)
{
	if (!philo->data_p->is_dead)
	{
		ft_lock_print("sleeping", philo);
		ft_usleep(philo->data_p->time_to_sleep);
	}
}

void	*routine(void *argument)
{
	t_philo	*philo;

	philo = (t_philo *)argument;
	if (philo->id % 2 == 0)
	{
		ft_usleep(philo->data_p->time_to_eat - 10);
	}
	while (!philo->data_p->is_dead)
	{
		if (philo->data_p->num_philos == 1)
		{
			eating_1philo(philo);
			break ;
		}
		else
			eating(philo);
		sleping(philo);
		thinking(philo);
	}
	return (NULL);
}
