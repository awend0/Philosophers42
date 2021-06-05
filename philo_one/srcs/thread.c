#include <philosophers.h>

int	philo_one_launch(t_all all)
{
	int	i;

	i = 0;
	while (i < all.global->amount)
	{
		if (pthread_create(&all.philos[i].thread, 0, philo_one_routine,
				&all.philos[i]) || pthread_detach(all.philos[i].thread))
		{
			print_error(strerror(errno));
			return (1);
		}
		i++;
	}
	i = 0;
	return (0);
}

void	*philo_one_observer(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->life);
		if (get_time() > philo->dead_time)
		{
			print_log(philo, MSG_DIED);
			pthread_mutex_unlock(&philo->life);
			pthread_mutex_unlock(&philo->global->dead);
		}
		pthread_mutex_unlock(&philo->life);
		usleep(1000);
	}
}

void	*philo_one_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	observer;

	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	philo->dead_time = philo->last_meal + philo->global->time_to_die;
	if (pthread_create(&observer, 0, philo_one_observer, arg)
		|| pthread_detach(observer))
		return ((void *)1);
	while (1)
	{
		philo_one_take_forks(philo);
		philo_one_eat(philo);
		philo_one_put_forks(philo);
		print_log(philo, MSG_THINKING);
	}
	return ((void *)0);
}
