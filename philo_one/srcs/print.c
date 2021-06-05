#include "philosophers.h"

char	*get_msg(int type)
{
	if (type == MSG_DIED)
		return (" died\n");
	else if (type == MSG_EATING)
		return (" is eating\n");
	else if (type == MSG_FORK)
		return (" has taken a fork\n");
	else if (type == MSG_SLEEPING)
		return (" is sleeping\n");
	else if (type == MSG_THINKING)
		return (" is thinking\n");
	return (" they ate enough...\n");
}

int	ft_strlen(char *str)
{
	int	ret;

	ret = 0;
	while (*str)
	{
		ret++;
		str++;
	}
	return (ret);
}

int	ft_putchar(char c)
{
	if (write(1, &c, 1) < 0)
		return (1);
	return (0);
}

int	ft_putstr(char *str)
{
	if (write(1, str, ft_strlen(str)) < 0)
		return (1);
	return (0);
}

void	ft_putnbr(int n)
{
	unsigned int	nbr;

	nbr = n;
	if (n < 0)
	{
		ft_putchar('-');
		nbr *= -1;
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else
		ft_putchar(nbr + '0');
}
