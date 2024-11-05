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

long	current_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int time_input_ms)
{
	long satart_time;

	satart_time = current_time();
	while(current_time() - satart_time < time_input_ms)
		usleep(100);
}
