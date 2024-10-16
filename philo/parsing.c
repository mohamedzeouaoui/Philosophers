#include "philo.h"

void    cheack_parms(int ac, char **av)
{
    int i;

    if (ac != 6 && ac != 5)
        print_error("nombre of arguments (Expected 5 or 6)");
    cheack_numbers(ac, av);
}

void cheack_numbers(int ac, char **av)
{
    int i;
    int j;

    j = 1;
    while(j < ac)
    {
        i = 0;
        while (av[j][i])
        {
            if (ft_isdigit(av[j][i]))
                i++;
            else
            {
                printf("Argument %d ", j);
                print_error("is not valid (we need numbers)");
            }
        }
        j++;
    }
}
// void    cheack_input_error(t_philo *philo)
// {
//     char *s;

//     s = "number_of_philosophers shouled be betwin 1 and 200 \n";

//     if(philo->num_of_philos > 200)
//         print_error(s);
//     if(philo->time_to_die < 60)
//         print_error("time_to_die should be larger than 60 ms.\n");
//     if(philo->time_to_eat < 60)
//         print_error("time_to_eat should be larger than 60 ms.\n");
//     if(philo->time_to_sleep < 60)
//         print_error("time_to_sleep should be larger than 60 ms.\n");
    
// }

