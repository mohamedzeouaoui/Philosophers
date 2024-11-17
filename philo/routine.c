#include "philo.h"

void    eating_1philo(t_philo *philo)
{
    if (philo->data_p->num_philos == 1)
    {
        pthread_mutex_lock(philo->right_fork);
        printf("%ld  %d  take a right fork\n", (current_time() - philo->data_p->start_time), philo->id);
        ft_usleep(philo->data_p->time_to_die);
        pthread_mutex_unlock(philo->right_fork);

    }
    return ;
}


void eating(t_philo *philo)
{
    // condition: if (numof_philos == 1): take own fork sleep time to die return ;
    // if (philo->data_p->num_philos == 1)
    //     return eating_1philo(philo);
    pthread_mutex_lock(philo->right_fork);
    printf("%ld  %d  take a right fork\n", (current_time() - philo->data_p->start_time), philo->id);
    pthread_mutex_lock(philo->left_fork);
	// pthread_mutex_lock(&philo->data_p->print_lock);

    printf("%ld  %d  take a left fork\n",(current_time() - philo->data_p->start_time), philo->id);
	// pthread_mutex_unlock(&philo->data_p->print_lock);
    printf("%ld  %d  is  eating\n", (current_time() - philo->data_p->start_time), philo->id);
    // printf("%ld\n", current_time());
    
    update_last_meal_time(philo);

    ft_usleep(philo->data_p->time_to_eat);

    // printf(".....lst in eat.......%ld...\n", philo->last_meal_time);
    // printf("............%d...\n", philo->data_p->time_to_eat);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    philo->meals_eaten = philo->meals_eaten + 1;

}

void thinking(t_philo *philo)
{
	// pthread_mutex_lock(&philo->think);
    printf("%ld  %d  thinking\n", (current_time() - philo->data_p->start_time), philo->id);
	// pthread_mutex_unlock(&philo->think);
}

void sleping(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data_p->print_lock);
    printf("%ld  %d  sleping\n",(current_time() - philo->data_p->start_time), philo->id);
	// pthread_mutex_unlock(&philo->data_p->print_lock);
    
    ft_usleep(philo->data_p->time_to_sleep);    
}

void routine(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        ft_usleep(philo->data_p->time_to_eat - 10);
    }
    // int i=0;
    while (1)
    {
        if (philo->data_p->num_philos == 1)
        {
            eating_1philo(philo);
            break;
        }
        else
            eating(philo);
        sleping(philo);

        thinking(philo);

        // i++;
    }
}
