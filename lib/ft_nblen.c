#include "../includes/minishell.h"

size_t	ft_nblen(long long nb)
{
	size_t	len;

	len = 0;
	if (!nb)
		return (1);
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}
