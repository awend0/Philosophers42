#include "../includes/philosophers.h"

static int	init_params_fill(t_params **tmp, int argc, char *argv[])
{
	t_params	*ret;

	ret = *tmp;
	if (argc < 5 || argc > 6)
		return (print_error("Wrong amount of arguments"));
	ret->amount = ft_atoi(argv[1]);
	if (ret->amount < 2 || ret->amount > 200)
		return (print_error("Wrong amount of philosophers"));
	ret->t_die = ft_atoi(argv[2]);
	if (ret->t_die < 60)
		return (print_error("Too short time to die"));
	ret->t_eat = ft_atoi(argv[3]);
	if (ret->t_eat < 60)
		return (print_error("Too short time to eat"));
	ret->t_sleep = ft_atoi(argv[4]);
	if (ret->t_sleep < 60)
		return (print_error("Too short time to sleep"));
	ret->eat_limit = 0;
	if (argc == 6)
		ret->eat_limit = ft_atoi(argv[5]);
	if (ret->eat_limit < 0)
		return (print_error("Wrong eat limit"));
	ret->fed_amount = 0;
	ret->last_msg = 0;
	return (0);
}

static int	init_params(t_params **tmp, int argc, char *argv[])
{
	t_params	*ret;

	ret = ft_calloc(sizeof(t_params));
	if (!ret)
		return (print_error("Malloc error"));
	if (init_params_fill(&ret, argc, argv))
	{
		free (ret);
		return (1);
	}
	ret->m_forks = ft_calloc(sizeof(t_mutex) * ret->amount);
	if (!ret->m_forks)
	{
		free (ret);
		return (print_error("Malloc error"));
	}
	pthread_mutex_init(&ret->m_print, 0);
	pthread_mutex_init(&ret->m_stop, 0);
	pthread_mutex_lock(&ret->m_stop);
	*tmp = ret;
	return (0);
}

static int	init_philos(t_philo **tmp, t_params *params)
{
	t_philo	*ret;
	int		i;

	ret = ft_calloc(sizeof(t_philo) * params->amount);
	if (!ret)
		return (1);
	i = 0;
	while (i < params->amount)
	{
		ret[i].index = i;
		ret[i].left_fork = i;
		ret[i].right_fork = (i + 1) % params->amount;
		ret[i].t_wdead = 0;
		ret[i].last_eat = 0;
		ret[i].params = params;
		ret[i].eat_amount = 0;
		pthread_mutex_init(&params->m_forks[i], 0);
		pthread_mutex_init(&ret[i].m_eat, 0);
		i++;
	}
	*tmp = ret;
	return (0);
}

int	init_all(t_philo **tmp, int argc, char *argv[])
{
	t_philo		*ret;
	t_params	*params;

	params = 0;
	if (init_params(&params, argc, argv))
		return (1);
	if (init_philos(&ret, params))
		return (1);
	*tmp = ret;
	return (0);
}
