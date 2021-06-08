#include "../includes/philosophers.h"

sem_t	*sem_create(char *name, int value)
{
	sem_t	*ret;

	sem_unlink(name);
	ret = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	return (ret);
}

static void	free_all(t_philo *philos)
{
	int		i;

	ft_usleep((philos->params->t_die + philos->params->t_sleep) * 1500);
	i = 0;
	while (i < philos->params->amount)
	{
		sem_close(philos[i].s_eat);
		sem_unlink(philos[i].s_eat_name);
		free (philos[i].s_eat_name);
		i++;
	}
	sem_close(philos->params->s_forks);
	sem_unlink(SEM_FORKS);
	sem_close(philos->params->s_print);
	sem_unlink(SEM_PRINT);
	sem_close(philos->params->s_stop);
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
