#include "../includes/minishell.h"

void	*ft_calloc(size_t size)
{
	void	*ptr;

	ptr = gc_malloc(size);
	ft_bzero(ptr, size);
	return (ptr);
}
