#include "../includes/philosophers.h"

int	print_error(char *str)
{
	char	*buf;

	ft_putstr("Error: ");
	ft_putstr(str);
	ft_putchar('\n');
	return (1);
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
