#include "philosophers.h"

int	philo_one_launch(t_all all)
{
	int			i;
	pthread_t	tmp;

	i = 0;
	all.global->started_time = get_time();
	if (all.global->eat_amount)
	{
		if (pthread_create(&tmp, NULL, philo_one_counter, &all) || pthread_detach(tmp))
			return (1);
	}
	while (i < all.global->amount)
	{
		if (pthread_create(&tmp, 0, philo_one_routine,
				&all.philos[i]) || pthread_detach(tmp))
		{
			print_error(strerror(errno));
			return (1);
		}
		usleep(100);
		i++;
	}
	i = 0;
	return (0);
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

void	*philo_one_observer(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->life);
		if (!philo->is_eating && get_time() > philo->dead_time)
		{
			print_log(philo, MSG_DIED);
			pthread_mutex_unlock(&philo->life);
			pthread_mutex_unlock(&philo->global->dead);
		}
		pthread_mutex_unlock(&philo->life);
		usleep(100);
	}
}

void	*philo_one_counter(void *arg)
{
	t_all		*all;
	int			count;
	int			i;

	count = 0;
	all = arg;
	while (count < all->global->eat_amount)
	{
		i = 0;
		while (i < all->global->amount)
		{
			pthread_mutex_lock(&all->philos[i].eat);
			i++;
		}
		count++;
	}
	print_log(&all->philos[0], MSG_LIMIT);
	pthread_mutex_unlock(&all->global->dead);
	return ((void *)0);
}
