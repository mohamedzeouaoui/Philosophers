#include "philo.h"

void eating(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    printf("%d : take a right fork\n", philo->id);
    pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data_p->print_lock);

    printf("%d : take a left fork\n", philo->id);
	pthread_mutex_unlock(&philo->data_p->print_lock);
    
    ft_usleep(philo->data_p->time_to_eat);

    printf("%d : eating\n", philo->id);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);


}

void thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_p->print_lock);
    printf("%d : thinking\n", philo->id);
	pthread_mutex_unlock(&philo->data_p->print_lock);
}

void sleping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_p->print_lock);
    printf("%d : sleping\n", philo->id);
	pthread_mutex_unlock(&philo->data_p->print_lock);
    
    ft_usleep(philo->data_p->time_to_sleep);    
}

void routine(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        ft_usleep(100);
    }
    int i=0;
    while (i < 6)
    {
        
        eating(philo);
        sleping(philo);

        thinking(philo);

        i++;
    }
    
}
