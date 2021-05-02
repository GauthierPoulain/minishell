#include "../includes/minishell.h"

size_t	ft_tab_len(char **car)
{
	size_t	res;

	res = 0;
	while (*car++)
		res++;
	return (res);
}
