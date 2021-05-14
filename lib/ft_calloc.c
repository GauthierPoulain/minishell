#include "../includes/minishell.h"

void	*ft_calloc(size_t size)
{
	void	*ptr;

	ptr = gc_malloc(size);
	ft_bzero(ptr, size);
	return (ptr);
}

void	*ft_calloc_char(size_t size, char c)
{
	char	*ptr;
	char	*uwu;

	ptr = ft_calloc(size);
	uwu = ptr;
	size--;
	while (size--)
		*ptr++ = c;
	return (uwu);
}
