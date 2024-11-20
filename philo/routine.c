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

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_p->check_death);
	if (philo->id % 2 == 0 && !philo->data_p->is_dead)
	{
		pthread_mutex_unlock(&philo->data_p->check_death);
		eating_pair(philo);
	}
	if (philo->id % 2 == 1 && !philo->data_p->is_dead)
	{
		pthread_mutex_unlock(&philo->data_p->check_death);
		eating_inpair(philo);
	}
	pthread_mutex_lock(&philo->cheack_num_eat_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->cheack_num_eat_mutex);
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

long	calcule_time_impair(t_philo *philo)
{
	long	nb;

	nb = (philo->data_p->time_to_die - (current_time()
				- philo->last_meal_time));
	return (nb / 2);
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
		if (philo->data_p->num_philos % 2)
		{
			ft_usleep(calcule_time_impair(philo));
		}
	}
	return (NULL);
}
