#include "philo.h"

int main(int ac, char **av)
{
    t_data data;

    cheack_parms(ac, av);
    initial_data(ac, av, &data);

    // while(1);

    // int i = 0;
    // while (i < data->num_philos)
    // {
    //     pthread_join(data->philo[i].thread, NULL);
    //     i++;
    // }
    // free(data.philo);
    return 0;

}