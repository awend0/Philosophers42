#include "../includes/philosophers.h"

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
	pthread_mutex_lock(&philos->params->m_stop);
	return (0);
}
