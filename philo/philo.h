#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct s_philo
{
    pthread_t   thread;
    int id;
    int eating;
    int meals_eating;
    size_t  last_meal;
    size_t  time_to_die;
    size_t  time_to_eat;
    size_t  time_to_sleep;
    size_t  start_time;
    int num_of_philos;
    int num_times_to_eat;
    int *dead;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *meal_lock;

}   t_philo;

typedef struct s_program
{
    int dead_flag;
    pthread_t   dead_lock;
    pthread_t   meal_lock;
    pthread_t   write_lock;
    t_philo *philos;

}   t_program;



void    cheack_parms(int ac, char **av);
void print_error(char *message_error);
int	ft_isdigit(int c);
void cheack_numbers(int ac, char **av);
int	ft_atoi(char *str);
void initial_data(int ac, char **av, t_philo *philo, t_program *data);
void    cheack_input_error(t_philo *philo);



#endif