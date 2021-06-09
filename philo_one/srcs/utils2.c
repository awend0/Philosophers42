#include "../includes/philosophers.h"

void	*ft_calloc(int size)
{
	void	*ret;

	ret = malloc(size);
	memset(ret, 0, size);
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	char	*buf_strjoin;
	int		s1_len;
	int		s2_len;

	if (!s2)
		return ((char *)s1);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	strjoin = ft_calloc(s1_len + s2_len + 1);
	if (!strjoin)
		return (0);
	buf_strjoin = strjoin;
	while (*s1)
		*strjoin++ = *s1++;
	while (*s2)
		*strjoin++ = *s2++;
	*strjoin = '\0';
	return (buf_strjoin);
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

static int	ft_nbrlen(int n)
{
	int		ret;

	ret = 0;
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
	buf = ft_calloc(nbrlen + 1);
	buf[nbrlen] = 0;
	i = 1;
	while (i <= nbrlen)
	{
		buf[nbrlen - i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	return (buf);
}
