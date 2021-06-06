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
	return ("died\n");
}

void	print_log(t_philo *philo, int type)
{
	int		time_stamp;

	pthread_mutex_lock(&philo->params->m_print);
	time_stamp = get_time() - philo->params->t_started;
	ft_putnbr(time_stamp);
	ft_putchar(' ');
	ft_putnbr(philo->index + 1);
	ft_putchar(' ');
	ft_putstr(get_msg(type));
	pthread_mutex_unlock(&philo->params->m_print);
}

int	print_error(char *str)
{
	ft_putstr("Error: ");
	ft_putstr(str);
	ft_putchar('\n');
	return (1);
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
