#include "philo.h"

int main(int ac, char **av) {
    t_philo philo;
    t_program datal;

    cheack_parms(ac, av);
    initial_data(ac, av, &philo, &data);    
    return 0;
}