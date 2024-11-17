#include "philo.h"

void *cheack_max_eating(t_data *data)
{
    int i;
    int cheack;

    while (1)
    {
        i = 0;
        cheack = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->philo[i].cheack_deid);
            if(data->philo[i].meals_eaten >= data->num_times_to_eat)
                cheack++;
            pthread_mutex_unlock(&data->philo[i].cheack_deid);
        
            i++;
        }
        if (cheack == data->num_philos)
        {
            printf("all eating");
            exit(0);
        }
        usleep(500);
    }
}






void *cheack_philo_died(void *ptr)
{
    int i;
    t_data *data;
    bool cheack;
    int ll = 0;

    cheack = false;
    data = (t_data*)ptr;
    while (!cheack)
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->philo[i].cheack_deid);

            // cheack_max_eating(data);
            // printf("hhhhhhh   id %d  hhhhhhhhhh  %d  hhhhhhhhhhhh\n",data->philo[i].id ,data->philo[i].meals_eaten);
            if (current_time() - data->philo[i].last_meal_time > data->time_to_die)
            {
                printf("philosopher %d has died\n", data->philo[i].id);
                cheack = true;
                pthread_mutex_unlock(&data->philo[i].cheack_deid);
                exit(1);
                // return NULL;
            }
            pthread_mutex_unlock(&data->philo[i].cheack_deid);

        	// pthread_mutex_lock(&data->philo[i].meals_mutex);

            if(data->philo[i].meals_eaten > data->num_times_to_eat && data->num_times_to_eat != -1)
                ll++;
        	// pthread_mutex_unlock(&data->philo[i].meals_mutex);
            
            i++;
        }
        if (ll == data->num_philos)
        {
            // printf("all eating\n");
            exit(0);
        }
    }
    return NULL;
}

void update_last_meal_time(t_philo *philosopher)
{
    pthread_mutex_lock(&philosopher->cheack_deid);
    philosopher->last_meal_time = current_time();
    pthread_mutex_unlock(&philosopher->cheack_deid);
    // printf(".....last update.......%ld...\n", philosopher->last_meal_time);

}

long time_to_print(t_philo *philo)
{
    return ((current_time() - philo->data_p->start_time));
}
