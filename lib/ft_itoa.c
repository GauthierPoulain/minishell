#include "../includes/minishell.h"

char	*ft_itoa(int n)
{
	char		*res;
	int			count;
	int			i;
	long int	tmp;

	tmp = n;
	count = ft_nblen(n);
	if (tmp < 0 || count == 0)
		count++;
	res = gc_malloc(sizeof(char) * (count + 1));
	ft_bzero(res, count + 1);
	i = 0;
	if (tmp < 0)
	{
		tmp *= -1;
		res[i++] = '-';
	}
	while (count > i)
	{
		res[--count] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (res);
}
