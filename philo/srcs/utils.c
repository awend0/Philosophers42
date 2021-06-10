#include "../includes/philosophers.h"

void	ft_usleep(int n)
{
	struct timeval	start;
	struct timeval	step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&step, NULL);
		if (((step.tv_sec - start.tv_sec) * 1000000
				+ (step.tv_usec - start.tv_usec)) > n)
			break ;
	}
}

int	get_time(void)
{
	static struct timeval	time;
	int						ret;

	gettimeofday(&time, 0);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

int	print_error(char *msg)
{
	printf("Error: %s.\n", msg);
	return (1);
}

static char	*get_msg(int type)
{
	if (type == MSG_FORK)
		return ("has taken a fork\n");
	else if (type == MSG_EAT)
		return ("is eating\n");
	else if (type == MSG_SLEEP)
		return ("is sleeping\n");
	else if (type == MSG_THINK)
		return ("is thinking\n");
	else if (type == MSG_DEAD)
		return ("died\n");
	return ("they ate enough\n");
}

void	print_log(t_philo *philo, int type)
{
	int		time_stamp;
	char	*buf;

	pthread_mutex_lock(&philo->params->m_print);
	if (!philo->params->last_msg)
	{	
		time_stamp = get_time() - philo->params->t_started;
		buf = ft_itoa(time_stamp);
		ft_putstr(buf);
		if (buf)
			free (buf);
		if (type != MSG_LIMIT)
		{
			buf = ft_itoa(philo->index + 1);
			ft_putstr(buf);
			if (buf)
				free (buf);
		}
		ft_putstr(get_msg(type));
		if (type == MSG_DEAD || type == MSG_LIMIT)
			philo->params->last_msg = 1;
	}
	pthread_mutex_unlock(&philo->params->m_print);
}
