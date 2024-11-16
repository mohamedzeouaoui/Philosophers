

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>



// typedef struct t_data;
struct s_data;


typedef struct s_philo
{
    pthread_t   thread;
    int id;                         // Philosopher ID
    int meals_eaten;                // Number of meals eaten
    long last_meal_time;            // Time of the last meal
    // pthread_mutex_t meal_mutex ;
    pthread_mutex_t think;
    pthread_mutex_t cheack_deid;
    pthread_mutex_t *left_fork;     // Pointer to the left fork
    pthread_mutex_t *right_fork;    // Pointer to the right fork
    struct s_data *data_p;
}   t_philo;


typedef struct s_data
{
    int num_philos;           // Total number of philosophers
    int time_to_die;                // Time until a philosopher dies without eating
    int time_to_eat;                // Time required to eat
    int time_to_sleep;              // Time required to sleep
    int num_times_to_eat;
    int is_dead;                    // Flag to indicate if a philosopher has died
    long start_time;           // Time the simulation started
	// pthread_mutex_t		print_mutex;
    pthread_mutex_t meal_time_mutex;
    pthread_mutex_t *forks;         // Array of mutexes representing forks
    pthread_mutex_t print_lock;     // Mutex for printing to avoid race conditions
    t_philo *philo;    // Pointer to an array of philosopher structs
} t_data;




void    cheack_parms(int ac, char **av);
void print_error(char *message_error);
int	ft_isdigit(int c);
void cheack_numbers(int ac, char **av);
int	ft_atoi(char *str);
void initial_data(int ac, char **av, t_data *data);
void routine(t_philo *philo);

void    cheack_input_error(t_philo *philo);
void	ft_usleep(int time_input_ms);
void update_last_meal_time(t_philo *philosopher);
long	current_time(void);
void *cheack_philo_died(void *ptr);




#endif