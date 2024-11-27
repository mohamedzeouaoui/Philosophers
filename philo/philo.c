/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:48:02 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/11/19 21:48:04 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	if (cheack_parms(ac, av) == 1)
		return (1);
	data = malloc(sizeof(t_data));
	if (initial_data(ac, av, data) == 1)
	{
		free(data);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		free(data->philo[i].right_fork);
		i++;
	}
	free(data->philo);
	free(data);
	return (0);
}
