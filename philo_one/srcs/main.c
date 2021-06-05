#include "philosophers.h"

int	philo_one_free(t_all all, int ret)
{
	int		i;

	i = 0;
	while (i < all.global->amount)
	{
		pthread_mutex_destroy(&all.global->forks[i]);
		pthread_mutex_destroy(&all.philos[i].life);
		pthread_mutex_destroy(&all.philos[i].eat);
		i++;
	}
	pthread_mutex_destroy(&all.global->print);
	pthread_mutex_destroy(&all.global->dead);
	free (all.philos);
	free (all.global->forks);
	free (all.global);
	return (ret);
}

int	main(int argc, char *argv[])
{
	t_all	all;
	int		ret;

	all.global = init_global(argc, argv);
	if (!all.global)
		return (1);
	all.philos = init_philos(all.global);
	if (!all.philos)
		return (1);
	ret = philo_one_launch(all);
	pthread_mutex_lock(&all.global->dead);
	pthread_mutex_unlock(&all.global->dead);
	return (philo_one_free(all, ret));
}
