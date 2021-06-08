#include "../includes/philosophers.h"

static void	free_all(t_philo *philos)
{
	int		i;

	ft_usleep((philos->params->t_die + philos->params->t_sleep) * 1500);
	i = 0;
	while (i < philos->params->amount)
	{
		pthread_mutex_destroy(&philos->params->m_forks[i]);
		pthread_mutex_destroy(&philos[i].m_eat);
		i++;
	}
	pthread_mutex_destroy(&philos->params->m_print);
	pthread_mutex_destroy(&philos->params->m_stop);
	free (philos->params->m_forks);
	free (philos->params);
	free (philos);
}

static int	launch_philo(t_philo *philos, int cmp)
{
	int			i;
	pthread_t	tmp;

	i = cmp;
	while (i < philos->params->amount)
	{
		if (pthread_create(&tmp, 0, &routine_philo, &philos[i])
			|| pthread_detach(tmp))
			return (print_error(strerror(errno)));
		i += 2;
	}
	return (0);
}

static int	launch_all(t_philo *philos)
{
	philos->params->t_started = get_time();
	if (launch_philo(philos, 0) || launch_philo(philos, 1))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo	*philos;

	if (init_all(&philos, argc, argv))
		return (1);
	if (launch_all(philos))
		return (1);
	pthread_mutex_lock(&philos->params->m_stop);
	free_all(philos);
	return (0);
}
