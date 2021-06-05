#include <philosophers.h>

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
	printf("Error: %s\n", err);
	return (0);
}

void	print_log(t_philo *philo, int type)
{
	int		time_stamp;

	pthread_mutex_lock(&philo->global->print);
	time_stamp = get_time() - philo->global->started_time;
	if (type == MSG_DIED)
		printf("%d\t%d died\n", time_stamp, philo->index + 1);
	else if (type == MSG_EATING)
		printf("%d\t%d is eating\n", time_stamp, philo->index + 1);
	else if (type == MSG_SLEEPING)
		printf("%d\t%d is sleeping\n", time_stamp, philo->index + 1);
	else if (type == MSG_THINKING)
		printf("%d\t%d is thinking\n", time_stamp, philo->index + 1);
	else if (type == MSG_FORK)
		printf("%d\t%d has taken a fork\n", time_stamp, philo->index + 1);
	else if (type == MSG_LIMIT)
		printf("%d\t%d must eat count reached\n", time_stamp, philo->index + 1);
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
