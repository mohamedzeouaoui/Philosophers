#include "philo.h"

void print_error(char *message_error)
{
    printf("Error: ");
    printf("%s\n", message_error);
    exit(EXIT_FAILURE);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	ft_atoi(char *str)
{
	int	nmb;

	nmb = 0;
	while (*str >= '0' && *str <= '9')
	{
		nmb = nmb * 10;
		nmb += *str - '0';
		str++;
	}
	return (nmb);
}
