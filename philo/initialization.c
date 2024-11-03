#include "philo.h"

void parsing_argc(int ac, char **av, t_data *data)
{
    int i;

    i = 1;
    while (i < ac)
    {
        if(i == 1)
            data->num_philos = ft_atoi(av[1]);
        else if(i == 2)
            data->time_to_die = ft_atoi(av[2]);
        else if(i == 3)
            data->time_to_eat = ft_atoi(av[3]);
        else if(i == 4)
            data->time_to_sleep = ft_atoi(av[4]);
        else if(i == 5)
            data->num_times_to_eat = ft_atoi(av[5]);
        i++;
    }

}
void    initial_forks(t_data *data)

{
    int nb;
    int i;

    i = 0;
    nb = 0;
    while (nb < data->num_philos)
        data->philo[nb++].right_fork = malloc(sizeof(pthread_mutex_t));
    while (i < data->num_philos)
    {
        pthread_mutex_init(data->philo[i].right_fork, NULL);
        if (i == 0)
            data->philo[i].left_fork = data->philo[data->num_philos - 1].right_fork;
        else
            data->philo[i].left_fork = data->philo[i - 1].right_fork;
        data->philo[i].data_p = data;
           
        data->philo[i].id = i + 1; 
        i++;
    }
    pthread_mutex_init(&data->print_lock, NULL);
	// pthread_mutex_lock(&data->print_lock);
	// pthread_mutex_unlock(&data->print_lock);

}

void *handel(void *argument)
{
    t_philo *philo;

    philo = (t_philo *)argument;
    routine(philo);


    return (NULL);
}

void    thread_create(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_create(&data->philo[i].thread, NULL, handel, &data->philo[i]);
        i++;
    }
    // printf("loooooooooool");
    i = 0;
    while (i < data->num_philos)
    {
        pthread_join(data->philo[i].thread, NULL);
        i++;
    }
   
    

}

void initial_data(int ac, char **av, t_data *data)
{
    int nb;

    nb = 0;
    parsing_argc(ac, av, data);
    data->philo = malloc(data->num_philos * sizeof(t_philo));
    memset(data->philo, 0, sizeof(t_philo) * data->num_philos);
    // data->philo->data_p = data;
    initial_forks(data);
    thread_create(data);


}