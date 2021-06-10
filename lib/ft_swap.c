#include "../includes/minishell.h"

void	ft_swap(t_ptoken *a, t_ptoken *b)
{
	t_ptoken	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
