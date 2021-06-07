#include "../includes/philosophers.h"

void	lifespan_take_forks(t_philo *philo)
{
	sem_wait(philo->params->s_forks);
	print_log(philo, MSG_FORK);
	sem_wait(philo->params->s_forks);
	print_log(philo, MSG_FORK);
}

void	lifespan_put_forks(t_philo *philo)
{
	sem_post(philo->params->s_forks);
	sem_post(philo->params->s_forks);
	print_log(philo, MSG_SLEEP);
	ft_usleep(philo->params->t_sleep * 1000);
}

void	lifespan_eat(t_philo *philo)
{
	sem_wait(philo->s_eat);
	philo->last_eat = get_time();
	philo->t_wdead = philo->last_eat + philo->params->t_die;
	philo->eat_amount++;
	if (philo->eat_amount >= philo->params->eat_limit)
		philo->params->fed_amount++;
	print_log(philo, MSG_EAT);
	ft_usleep(philo->params->t_eat * 1000);
	sem_post(philo->s_eat);
}
