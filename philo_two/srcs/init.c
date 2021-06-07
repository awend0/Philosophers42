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

	ret = malloc(sizeof(t_params));
	if (!ret)
		return (print_error("Malloc error"));
	if (init_params_fill(&ret, argc, argv))
	{
		free (ret);
		return (1);
	}
	ret->s_print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	ret->s_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, ret->amount);
	ret->s_stop = sem_open(SEM_STOP, O_CREAT | O_EXCL, 0644, 0);
	*tmp = ret;
	return (0);
}

static int	init_philos(t_philo **tmp, t_params *params)
{
	t_philo	*ret;
	int		i;

	ret = malloc(sizeof(t_philo) * params->amount);
	if (!ret)
		return (1);
	i = 0;
	while (i < params->amount)
	{
		ret[i].index = i;
		ret[i].t_wdead = 0;
		ret[i].last_eat = 0;
		ret[i].params = params;
		ret[i].eat_amount = 0;
		ret[i].s_eat_name = get_sem_name(i);
		ret[i].s_eat = sem_open(ret[i].s_eat_name, O_CREAT | O_EXCL, 0644, 1);
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
