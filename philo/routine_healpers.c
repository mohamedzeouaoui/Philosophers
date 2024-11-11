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
    ft_usleep(data->time_to_die);
    while (!cheack)
    {
        curent_time = current_time();
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->philo[i].cheack_deid);


            mb = curent_time - data->philo[i].last_meal_time;
            // printf("...mb.........%d...\n", mb);
            
            // printf("......cur......%d...\n",  data->philo[i].id);
            // printf("...id : %d...last......%ld...\n",  data->philo[i].id ,data->philo[i].last_meal_time);

            if (curent_time - data->philo[i].last_meal_time > data->time_to_die)
            {
                printf("philosopher %d has died\n", data->philo[i].id);
                cheack = true;
                pthread_mutex_unlock(&data->philo[i].cheack_deid);
                return NULL;
            }
            i++;
            pthread_mutex_unlock(&data->philo[i].cheack_deid);
        }
        usleep(1000);
    }
    return NULL;
}

void update_last_meal_time(t_philo *philosopher)
{
    pthread_mutex_lock(&philosopher->data_p->meal_time_mutex);
    philosopher->last_meal_time = current_time();
    pthread_mutex_unlock(&philosopher->data_p->meal_time_mutex);
    // printf(".....last update.......%ld...\n", philosopher->last_meal_time);

}
