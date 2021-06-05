#include "philosophers.h"

void	philo_one_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->forks[philo->left_fork]);
	print_log(philo, MSG_FORK);
	pthread_mutex_lock(&philo->global->forks[philo->right_fork]);
	print_log(philo, MSG_FORK);
}

void	philo_one_put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->global->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->global->forks[philo->right_fork]);
	print_log(philo, MSG_SLEEPING);
	usleep(philo->global->time_to_sleep * 1000);
}

void	philo_one_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat);
	philo->is_eating = 1;
	philo->last_meal = get_time();
	philo->dead_time = philo->last_meal + philo->global->time_to_die;
	print_log(philo, MSG_EATING);
	usleep(philo->global->time_to_eat * 1000);
	philo->eat_amount++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eat);
	pthread_mutex_unlock(&philo->life);
}
