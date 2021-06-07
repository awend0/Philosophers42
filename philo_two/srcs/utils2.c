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

void	*ft_memcpy(void *dst, void *src, int n)
{
	char	*dest;
	char	*source;

	if (!src && !dst)
		return (0);
	source = src;
	dest = dst;
	dest[n] = '\0';
	while (n--)
		*dest++ = *source++;
	return (dst);
}

char	*ft_strcpy(char *dst, char *src)
{
	int	len;

	len = ft_strlen(src);
	ft_memcpy(dst, src, len + 1);
	return (dst);
}

char	*ft_itoa(int n)
{
	char	*str;

	str = ft_calloc(2);
	if (n == -2147483648)
		return (ft_strcpy(str, "-2147483648"));
	if (n < 0)
	{
		str[0] = '-';
		str[1] = '\0';
		str = ft_strjoin(str, ft_itoa(-n));
	}
	else if (n >= 10)
		str = ft_strjoin(ft_itoa(n / 10), ft_itoa(n % 10));
	else if (n < 10 && n >= 0)
	{
		str[0] = n + '0';
		str[1] = '\0';
	}
	return (str);
}
