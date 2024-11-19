#include "philo.h"

void parsing_argc(int ac, char **av, t_data *data)
{
    int i;

    i = 1;
    data->num_times_to_eat = -1;
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
   // sleep(1);

    while (nb < data->num_philos){
        data->philo[nb++].right_fork = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    }
    // printf("hhhhhhhhhhhh");
    while (i < data->num_philos)
    {
        pthread_mutex_init(data->philo[i].right_fork, NULL);
        if (i == 0 && data->num_philos != 1)
            data->philo[i].left_fork = data->philo[data->num_philos - 1].right_fork;
        else if ( data->num_philos != 1)
            data->philo[i].left_fork = data->philo[i - 1].right_fork;
        data->philo[i].data_p = data;
           
        data->philo[i].id = i + 1; 
        pthread_mutex_init(&data->philo[i].cheack_deid, NULL);
        pthread_mutex_init(&data->philo[i].meals_mutex , NULL);
        i++;

    }
    pthread_mutex_init(&data->write_lock, NULL);
    pthread_mutex_init(&data->meal_time_mutex, NULL);
    pthread_mutex_init(&data->check_death, NULL);

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
    // pthread_t monitor;

    i = 0;
    data->start_time = current_time();
    while (i < data->num_philos)
    {
        pthread_create(&data->philo[i].thread, NULL, handel, &data->philo[i]);
        i++;
    }
    // pthread_create(&monitor, NULL, cheack_philo_died, data);
    // create new
    cheack_philo_died(data);


    i = 0;
    while (i < data->num_philos)
    {
        pthread_join(data->philo[i].thread, NULL);
        i++;
    }

    
    // pthread_join(monitor, NULL);
    


    // while (1) {
        // ft_usleep(data->time_to_die);
        // printf("hello word %ld \n", data->philo[0].last_meal_time);
        // if(cheack_philo_died(data))
            // break;
        // check for death
        // philo -> last time ate ith philo

        /*
            int i = 0;
            int count = 0;
            while (i < number of philo)
                    // curr time - last time of ate of the ith >= timw_to_die ==> death
                        || (optianl exists && all philo eat that number)
                        // if death break ;
                        all philo eat that number
                        count++ if ith philo ate num
                        if count == number of philo

            usleep(200);
        */
    // }
        // cheack_philo_died(data);
   
}

void initial_data(int ac, char **av, t_data *data)
{
    int nb;

    nb = 0;
    parsing_argc(ac, av, data);
    data->philo = (t_philo *)malloc((data->num_philos) * sizeof(t_philo));
    if (data->philo == NULL){
        puts("malloc failed");
        return ;
    }
    memset(data->philo, 0, sizeof(t_philo) * data->num_philos);
    data->is_dead = false ;
    data->is_errore = false ;

    nb  = 0;
    while (data->num_philos > nb)
    {
        data->philo[nb].last_meal_time = current_time();
        nb++;
    }
    initial_forks(data);
    thread_create(data);


}