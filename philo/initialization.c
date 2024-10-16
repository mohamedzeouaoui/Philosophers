#include "philo.h"

void parsing_argc(int ac, char **av, t_philo *philo)
{
    int i;

    i = 1;
    while (i < ac)
    {
        if(i == 1)
            philo->num_of_philos = ft_atoi(av[1]);
        else if(i == 2)
            philo->time_to_die = ft_atoi(av[2]);
        else if(i == 3)
            philo->time_to_eat = ft_atoi(av[3]);
        else if(i == 4)
            philo->time_to_sleep = ft_atoi(av[4]);
        else if(i == 5)
            philo->num_times_to_eat = ft_atoi(av[5]);
        i++;
    }
    

}

void initial_data(int ac, char **av, t_philo *philo, t_program *data)
{
    memset(philo, 0, sizeof(t_philo));
    parsing_argc(ac, av, philo);
    // cheack_input_error(philo);
    philo = malloc(philo->num_of_philos * sizeof(t_philo)); 
    data->philos = philo;
}