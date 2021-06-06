#include "../includes/philosophers.h"

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
