#include "philo.h"

void eating(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    printf("%d : take a right fork\n", philo->id);
    pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data_p->print_lock);

    printf("%d : take a left fork\n", philo->id);
	pthread_mutex_unlock(&philo->data_p->print_lock);
    update_last_meal_time(philo);
    printf("%d : is  eating\n", philo->id);
    
    ft_usleep(philo->data_p->time_to_eat);


    // printf(".....lst in eat.......%ld...\n", philo->last_meal_time);
    // printf("............%d...\n", philo->data_p->time_to_eat);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);


}

void thinking(t_philo *philo)
{
	// pthread_mutex_lock(&philo->think);
    printf("%d : thinking\n", philo->id);
	// pthread_mutex_unlock(&philo->think);
}

void sleping(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data_p->print_lock);
    printf("%d : sleping\n", philo->id);
	// pthread_mutex_unlock(&philo->data_p->print_lock);
    
    ft_usleep(philo->data_p->time_to_sleep);    
}

void routine(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        ft_usleep(100);
    }
    // int i=0;
    while (1)
    {
        
        eating(philo);
        sleping(philo);

        thinking(philo);

        // i++;
    }
}
