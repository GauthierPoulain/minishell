#include "../includes/minishell.h"

void	*ft_calloc(size_t size)
{
	void	*ptr;

	ptr = gc_malloc(size);
	ft_bzero(ptr, size);
	return (ptr);
}

void	*ft_calloc_char(size_t size, int c)
{
	char	*ptr;
	size_t	pos;

	ptr = ft_calloc(size + 1);
	if (size)
		size--;
	pos = 0;
	while (pos < size)
	{
		ptr[pos] = c;
		pos++;
	}
	return (ptr);
}
