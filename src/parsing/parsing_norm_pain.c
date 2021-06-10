#include "../../includes/minishell.h"

void	init_things(int *size, int *i)
{
	*i = 0;
	*size = ft_lstsize(g_shell.tokens);
}

int	do_both(t_list *lst, t_ptoken *array, int i)
{
	(array + i)->is_escaped = false;
	(array + i)->str = NULL;
	things(lst, array, i);
	if (g_shell.error)
		return (1);
	return (0);
}

int	check_things(t_list *lst)
{
	if (!((t_token *)lst->content)->sp && ((t_token *)lst->content)->id >= 1)
		return (1);
	return (0);
}
