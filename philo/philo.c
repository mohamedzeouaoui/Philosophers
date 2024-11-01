#include "philo.h"

int main(int ac, char **av)
{
    t_data data;

    cheack_parms(ac, av);
    initial_data(ac, av, &data);

    while(1);
    // free(data.philo);
    return 0;

}