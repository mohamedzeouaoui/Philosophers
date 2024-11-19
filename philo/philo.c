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

	data = malloc(sizeof(t_data));
	cheack_parms(ac, av);
	initial_data(ac, av, data);
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
