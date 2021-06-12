#include "../../includes/minishell.h"

void	init_things(int *size, int *i)
{
	*i = 0;
	*size = ft_lstsize(g_shell.tokens);
}

int	do_both(t_list *lst, t_ptoken *array, int i)
{
	(void)lst;
	(array + i)->is_escaped = false;
	(array + i)->need_join = false;
	(array + i)->is_in_quotes = false;
	(array + i)->is_in_squotes = false;
	(array + i)->str = NULL;
	if (g_shell.error)
		return (1);
	return (0);
}

int	check_things(t_list *lst)
{
	// if (((t_token *)lst->content)->id >= 1)
	// 	if (get_token_at(((t_token *)lst->content)->id - 1)->type == 3
	// 		&& !((t_token *)lst->content)->sp
	// 		&& ((t_token *)lst->content)->type == 4
	// 		&& ((t_token *)lst->content)->type == 6)
	// 			return (1);
	if (get_token_at(((t_token *)lst->content)->id)->type == 4 
		&& ((t_token *)lst->content)->id > 0
		&& get_token_at(((t_token *)lst->content)->id - 1)->type == 3)
	{
		// if (((t_token *)lst->content)->id >= 1)
			g_shell.is_in_quotes = !g_shell.is_in_quotes;
	}
	else if (get_token_at(((t_token *)lst->content)->id)->type == 6
		&& ((t_token *)lst->content)->id > 0
		&& get_token_at(((t_token *)lst->content)->id - 1)->type == 3)
		g_shell.is_in_s_quotes = !g_shell.is_in_s_quotes;
	if (!((t_token *)lst->content)->sp && !g_shell.is_in_s_quotes
		&& !g_shell.is_in_quotes && g_shell.trans && ((t_token *)lst->content)->id >= 1
		/*&& ((t_token *)lst->content)->type != 4 && ((t_token *)lst->content)->type != 6*/)
		return (1);
	return (0);
}

void	display_ptoken(t_ptoken *array)
{
	int	i;

	i = 0;
	while ((array + i)->str)
	{
		printf("(%s)dquotes:[%d]squotes:[%d]escaped:[%d]escapes[%d]\n", (array + i)->str, (array + i)->is_in_quotes, (array + i)->is_in_squotes, (array + i)->is_escaped, (array + i)->escapes);
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
