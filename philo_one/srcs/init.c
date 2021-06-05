#include "philosophers.h"

t_mutex	*init_forks(t_global *global)
{
	int		i;
	t_mutex	*ret;

	pthread_mutex_init(&global->print, 0);
	pthread_mutex_init(&global->dead, 0);
	pthread_mutex_lock(&global->dead);
	ret = malloc(sizeof(t_mutex) * global->amount);
	i = 0;
	while (i < global->amount)
	{
		pthread_mutex_init(&ret[i], 0);
		i++;
	}
	return (ret);
}

t_philo	*init_philos(t_global *global)
{
	t_philo	*ret;
	int		i;

	ret = malloc(sizeof(t_philo) * global->amount);
	i = 0;
	while (i < global->amount)
	{
		ret[i].index = i;
		ret[i].left_fork = i;
		ret[i].right_fork = (i + 1) % global->amount;
		ret[i].eat_amount = 0;
		ret[i].global = global;
		pthread_mutex_init(&ret[i].eat, 0);
		pthread_mutex_init(&ret[i].life, 0);
		pthread_mutex_lock(&ret[i].eat);
		i++;
	}
	return (ret);
}

t_global	*init_global(int argc, char *argv[])
{
	t_global	*ret;

	if (argc < 5 || argc > 6)
		return (print_error("Wrong amount of arguments"));
	ret = malloc(sizeof(t_global));
	ret->amount = ft_atoi(argv[1]);
	ret->time_to_die = ft_atoi(argv[2]);
	ret->time_to_eat = ft_atoi(argv[3]);
	ret->time_to_sleep = ft_atoi(argv[4]);
	ret->eat_amount = 0;
	if (argc == 6)
		ret->eat_amount = ft_atoi(argv[5]);
	ret->forks = init_forks(ret);
	return (ret);
}
