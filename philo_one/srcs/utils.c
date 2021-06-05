#include "philosophers.h"

int	get_time(void)
{
	static struct timeval	time;
	int						ret;

	gettimeofday(&time, 0);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

void	*print_error(char *err)
{
	ft_putstr("Error: ");
	ft_putstr(err);
	ft_putchar('\n');
	return (0);
}

void	print_log(t_philo *philo, int type)
{
	int			time_stamp;
	static int	final_msg;

	pthread_mutex_lock(&philo->global->print);
	if (!final_msg)
	{
		time_stamp = get_time() - philo->global->started_time;
		ft_putnbr(time_stamp);
		if (type != MSG_LIMIT)
		{
			ft_putchar(' ');
			ft_putnbr(philo->index + 1);
		}
		ft_putstr(get_msg(type));
		if (type == MSG_DIED || type == MSG_LIMIT)
			final_msg = 1;
	}
	pthread_mutex_unlock(&philo->global->print);
}

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi(char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && ft_isspace(*str))
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
