#include "philo.h"

// void *cheack_max_eating(t_data *data)
// {
//     int i;
//     int cheack;

//     while (1)
//     {
//         i = 0;
//         cheack = 0;
//         while (i < data->num_philos)
//         {
//             pthread_mutex_lock(&data->philo[i].cheack_deid);
//             if(data->philo[i].meals_eaten >= data->num_times_to_eat)
//                 cheack++;
//             pthread_mutex_unlock(&data->philo[i].cheack_deid);
        
//             i++;
//         }
//         if (cheack == data->num_philos)
//         {
//             printf("all eating");
//             exit(0);
//         }
//         usleep(500);
//     }
// }






void *cheack_philo_died(void *ptr)
{
    int i;
    t_data *data;
    int ll = 0;

    data = (t_data*)ptr;
    while (1)
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->philo[i].cheack_deid);

            if (current_time() - data->philo[i].last_meal_time > data->time_to_die)
            {
                pthread_mutex_lock(&data->check_death);
                pthread_mutex_lock(&data->write_lock);
                printf("%ld philosopher %d has died\n", current_time() - data->start_time, data->philo[i].id);
                pthread_mutex_unlock(&data->write_lock);

                data->is_dead = true;
                data->is_errore = true;
                pthread_mutex_unlock(&data->check_death);
                pthread_mutex_unlock(&data->philo[i].cheack_deid);
                return NULL;
            }

            pthread_mutex_unlock(&data->philo[i].cheack_deid);

            if(data->philo[i].meals_eaten > data->num_times_to_eat && data->num_times_to_eat != -1)
                ll++;
            i++;
        }
        if (ll == data->num_philos)
        {
            data->is_dead = true;
            return NULL;
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
