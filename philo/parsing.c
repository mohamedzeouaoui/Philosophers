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


