#include "../includes/philosophers.h"

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

int	ft_putstr(char *str)
{
	if (write(1, str, ft_strlen(str)) < 0)
		return (1);
	return (0);
}

static int	ft_nbrlen(int n)
{
	int		ret;

	ret = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		ret++;
		n *= -1;
	}
	while (n)
	{
		ret++;
		n /= 10;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char	*buf;
	int		nbrlen;
	int		i;

	nbrlen = ft_nbrlen(n);
	buf = malloc(nbrlen + 2);
	buf[nbrlen + 1] = 0;
	buf[nbrlen] = ' ';
	if (n == 0)
	{
		buf[0] = '0';
		return (buf);
	}
	i = 1;
	while (i <= nbrlen)
	{
		buf[nbrlen - i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	return (buf);
}
