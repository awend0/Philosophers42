#include <philosophers.h>

int	philo_one_free(t_all all, int ret)
{
	free(all.global->forks);
	free(all.philos);
	free(all.global);
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
	return (philo_one_free(all, ret));
}
