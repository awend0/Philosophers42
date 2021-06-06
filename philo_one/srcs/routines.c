#include "../includes/philosophers.h"

void    *routine_observer(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        pthread_mutex_lock(&philo->m_eat);
        if (get_time() > philo->t_wdead)
        {
            print_log(philo, MSG_DEAD);
            pthread_mutex_unlock(&philo->m_eat);
            pthread_mutex_unlock(&philo->params->m_stop);
        }
        pthread_mutex_unlock(&philo->m_eat);
    }
}

void    *routine_philo(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    philo->last_eat = get_time();
    philo->t_wdead = philo->last_eat + philo->params->t_die;
    while (1)
    {
        lifespan_take_forks(philo);
        lifespan_eat(philo);
        lifespan_put_forks(philo);
    }
    return ((void *)0);
}
