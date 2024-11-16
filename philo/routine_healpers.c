#include "philo.h"


void *cheack_philo_died(void *ptr)
{
    int i;
    long curent_time;
    int mb;
    t_data *data;
    bool cheack;

    cheack = false;
    data = (t_data*)ptr;
    // ft_usleep(data->time_to_die);
    while (!cheack)
    {
        curent_time = current_time();
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->philo[i].cheack_deid);
            mb = current_time() - data->philo[i].last_meal_time;
            if (mb > data->time_to_die)
            {
                printf("philosopher %d has died\n", data->philo[i].id);
                cheack = true;
                pthread_mutex_unlock(&data->philo[i].cheack_deid);
                exit(1);
                return NULL;
            }
            pthread_mutex_unlock(&data->philo[i].cheack_deid);
            i++;
        }
        // usleep(1000);
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
