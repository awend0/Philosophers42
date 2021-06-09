#include "../includes/philosophers.h"

int	print_error(char *str)
{
	ft_putstr("Error: ");
	ft_putstr(str);
	ft_putstr("\n");
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

int	ft_putstr(char *str)
{
	if (write(1, str, ft_strlen(str)) < 0)
		return (1);
	return (0);
}