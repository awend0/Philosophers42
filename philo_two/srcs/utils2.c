#include "../includes/philosophers.h"

void	*ft_calloc(int size)
{
	void	*ret;

	ret = malloc(size);
	memset(ret, 0, size);
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2, int _free)
{
	char	*strjoin;
	char	*buf_strjoin;
	char	*tmp;
	int		s1_len;
	int		s2_len;

	tmp = s1;
	if (!s2)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	strjoin = ft_calloc(s1_len + s2_len + 1);
	if (!strjoin)
		return (0);
	buf_strjoin = strjoin;
	while (*s1)
		*strjoin++ = *s1++;
	while (*s2)
		*strjoin++ = *s2++;
	*strjoin = '\0';
	if (_free)
		free(tmp);
	return (buf_strjoin);
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
