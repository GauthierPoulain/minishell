#include "../../includes/minishell.h"

void	init_things(int *size, int *i)
{
	*i = 0;
	*size = ft_lstsize(g_shell.tokens);
}

int	do_both(t_list *lst, t_ptoken *array, int i)
{
	(array + i)->is_escaped = false;
	(array + i)->need_join = false;
	(array + i)->str = NULL;
	things(lst, array, i);
	if (g_shell.error)
		return (1);
	return (0);
}

int	check_things(t_list *lst)
{
	if (((t_token *)lst->content)->id >= 1)
		if (get_token_at(((t_token *)lst->content)->id - 1)->type == 3
			&& !((t_token *)lst->content)->sp
			&& ((t_token *)lst->content)->type == 4)
				return (1);
	if (!((t_token *)lst->content)->sp && ((t_token *)lst->content)->id >= 1
		&& ((t_token *)lst->content)->type != 4)
		return (1);
	else if (get_token_at(((t_token *)lst->content)->id)->type == 4)
	{
		if (((t_token *)lst->content)->id >= 1)
			g_shell.is_in_quotes = !g_shell.is_in_quotes;
	}
	// else if (g_shell.is_in_quotes)
	// 	;
	return (0);
}

void	display_ptoken(t_ptoken *array)
{
	int	i;

	i = 0;
	while ((array + i)->str)
	{
		printf("(%s)[%d]\n", (array + i)->str, (array + i)->is_in_quotes);
		i++;
	}
}

int	get_array_size(t_ptoken *array)
{
	int	i;

	i = 0;
	while ((array + i)->str)
		i++;
	return (i);
}
