#include "../includes/minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*castd;
	const char	*casts;

	if (!dst && !src)
		return (NULL);
	castd = dst;
	casts = src;
	while (n--)
		*castd++ = *casts++;
	return (dst);
}
