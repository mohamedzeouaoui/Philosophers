/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:47:50 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/11/19 21:47:54 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cheack_parms(int ac, char **av)
{
	int	r;

	r = 0;
	if (ac != 6 && ac != 5)
	{ 
		r = print_error("nombre of arguments (Expected 5 or 6)");
		return(r);
	}
	r = cheack_numbers(ac, av);
	return (r);
}

int	cheack_numbers(int ac, char **av)
{
	int	i;
	int	j;
	int r;

	j = 1;
	r = 0;
	while (j < ac)
	{
		i = 0;
		while (av[j][i])
		{
			if (ft_isdigit(av[j][i]))
				i++;
			else
			{
				printf("Argument %d ", j);
				r = print_error("is not valid (we need numbers)");
				return(r);
			}
		}
		j++;
	}
	return(r);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
