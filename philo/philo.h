/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:48:10 by mzeouaou          #+#    #+#             */
/*   Updated: 2024/11/19 21:48:13 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// struct s_data;
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	bool			cheack_max_eat;
	pthread_mutex_t	cheack_num_eat_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	cheack_deid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data_p;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	bool			is_dead;
	bool			is_errore;
	long			start_time;

	pthread_mutex_t	died_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_time_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	check_death;
	t_philo			*philo;
}					t_data;

void				ft_print_deid(t_data *data, int i);
void				ft_lock_print(char *str, t_philo *p);
void				eating_pair(t_philo *philo);
void				eating_inpair(t_philo *philo);
void				eating_1philo(t_philo *philo);
int					cheack_parms(int ac, char **av);
int					print_error(char *message_error);
int					ft_isdigit(int c);
int					cheack_numbers(int ac, char **av);
long				ft_atoi(char *str);
void				ft_lock_print(char *str, t_philo *p);
int					initial_data(int ac, char **av, t_data *data);
void				*routine(void *argument);

int					ft_strlen(const char *str);
void				cheack_input_error(t_philo *philo);
void				ft_usleep(int time_input_ms);
void				update_last_meal_time(t_philo *philosopher);
long				current_time(void);
void				*cheack_philo_died(void *ptr);
long				time_to_print(t_philo *philo);
void				*cheack_max_eating(t_data *data);

#endif
