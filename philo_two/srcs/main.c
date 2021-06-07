#include "../includes/philosophers.h"

char	*get_sem_name(int index)
{
	char	*nbr;
	char	*ret;

	nbr = ft_itoa(index);
	ret = ft_strjoin("S_EAT", nbr);
	free (nbr);
	return (ret);
}

static void	free_all(t_philo *philos)
{
	int		i;

	ft_usleep((philos->params->t_die + philos->params->t_sleep) * 1500);
	i = 0;
	while (i < philos->params->amount)
	{
		sem_unlink(philos[i].s_eat_name);
		free (philos[i].s_eat_name);
		i++;
	}
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);
	free (philos->params);
	free (philos);
}

static int	launch_all(t_philo *philos)
{
	int			i;
	pthread_t	tmp;

	philos->params->t_started = get_time();
	i = 0;
	while (i < philos->params->amount)
	{
		if (pthread_create(&tmp, 0, &routine_philo, &philos[i])
			|| pthread_detach(tmp))
			return (print_error(strerror(errno)));
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo	*philos;

	if (init_all(&philos, argc, argv))
		return (1);
	if (launch_all(philos))
		return (1);
	sem_wait(philos->params->s_stop);
	free_all(philos);
	return (0);
}
