#include "../includes/philosophers.h"

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

	sem_wait(philo->params->s_print);
	if (!philo->params->last_msg)
	{
		time_stamp = get_time() - philo->params->t_started;
		ft_putnbr(time_stamp);
		ft_putchar(' ');
		if (type != MSG_LIMIT)
		{
			ft_putnbr(philo->index + 1);
			ft_putchar(' ');
		}
		ft_putstr(get_msg(type));
		if (type == MSG_DEAD || type == MSG_LIMIT)
			philo->params->last_msg = 1;
	}
	sem_post(philo->params->s_print);
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

int	ft_atoi(char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r' || *str == ' '))
		str++;
	if (*str == '-')
		negative = -1;
	while (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}
