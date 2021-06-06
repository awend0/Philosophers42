#include "../includes/philosophers.h"

void	lifespan_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->m_forks[philo->left_fork]);
	print_log(philo, MSG_FORK);
	pthread_mutex_lock(&philo->params->m_forks[philo->right_fork]);
	print_log(philo, MSG_FORK);
}

void	lifespan_put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->params->m_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->params->m_forks[philo->right_fork]);
	print_log(philo, MSG_SLEEP);
	usleep(philo->params->t_sleep * 1000);
}

void	lifespan_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_eat);
	philo->last_eat = get_time();
	philo->t_wdead = philo->last_eat + philo->params->t_die;
	philo->eat_amount++;
	print_log(philo, MSG_EAT);
	usleep(philo->params->t_eat * 1000);
	pthread_mutex_unlock(&philo->m_eat);
}
