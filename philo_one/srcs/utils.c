#include "../includes/philosophers.h"

static char	*get_msg(int type)
{
	if (type == MSG_FORK)
		return (" has taken a fork\n");
	else if (type == MSG_EAT)
		return (" is eating\n");
	else if (type == MSG_SLEEP)
		return (" is sleeping\n");
	else if (type == MSG_THINK)
		return (" is thinking\n");
	else if (type == MSG_DEAD)
		return (" died\n");
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
		buf = ft_strjoin(ft_itoa(time_stamp), " ", 0);
		if (type != MSG_LIMIT)
			buf = ft_strjoin(buf, ft_itoa(philo->index + 1), 1);
		buf = ft_strjoin(buf, get_msg(type), 0);
		if (type == MSG_DEAD || type == MSG_LIMIT)
			philo->params->last_msg = 1;
		ft_putstr(buf);
		free (buf);
	}
	pthread_mutex_unlock(&philo->params->m_print);
}

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
