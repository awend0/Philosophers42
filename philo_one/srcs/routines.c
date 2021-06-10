#include "../includes/philosophers.h"

void	*routine_observer(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->m_eat);
		if (philo->params->eat_limit > 0
			&& philo->params->fed_amount >= philo->params->amount)
		{
			print_log(philo, MSG_LIMIT);
			pthread_mutex_unlock(&philo->m_eat);
			pthread_mutex_unlock(&philo->params->m_stop);
			return ((void *)0);
		}
		if (get_time() > philo->t_wdead)
		{
			print_log(philo, MSG_DEAD);
			pthread_mutex_unlock(&philo->m_eat);
			pthread_mutex_unlock(&philo->params->m_stop);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->m_eat);
		ft_usleep(1000);
	}
}

void	*routine_philo(void *arg)
{
	t_philo		*philo;
	pthread_t	observer;

	philo = (t_philo *)arg;
	if (pthread_create(&observer, 0, routine_observer, arg)
		|| pthread_detach(observer))
		return ((void *)1);
	philo->last_eat = get_time();
	philo->t_wdead = philo->last_eat + philo->params->t_die;
	while (1)
	{
		if (philo->params->last_msg)
			break ;
		lifespan_take_forks(philo);
		lifespan_eat(philo);
		lifespan_put_forks(philo);
	}
	return ((void *)0);
}
