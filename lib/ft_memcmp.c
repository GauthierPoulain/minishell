#include "../includes/minishell.h"

int	ft_memcmp(const char *s1, const char *s2, size_t size)
{
	size_t	pos;

	if ((!s1 && s2) || (s1 && !s2))
		return (1);
	else if (!s1 && !s2)
		return (0);
	pos = 0;
	while (pos < size)
	{
		if (s1[pos] != s2[pos])
			return (s1[pos] - s2[pos]);
		pos++;
	}
	return (0);
}
