#include "../includes/minishell.h"

void	ft_bzero(void *s, size_t n)
{
	char	*casts;

	casts = (char *)s;
	while (n--)
		*casts++ = 0;
}
