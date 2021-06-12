#include "../../includes/minishell.h"

t_token	*init_ptoken(t_token *token, t_list *lst, \
t_ptoken *array, int i)
{
	token = lst->content;
	do_both(lst, array, i);
	(array + i)->str = token->str;
	(array + i)->is_in_quotes = g_shell.is_in_quotes;
	(array + i)->is_in_squotes = g_shell.is_in_s_quotes;
	return (token);
}

void	reset_g_shell(int i, t_token *token, t_ptoken *array)
{
	if (!g_shell.is_in_s_quotes && ((i == 0 && token->type == 4)
			|| (token->type == 4 && !(array + (i - 1))->escapes)))
		g_shell.is_in_quotes = !g_shell.is_in_quotes;
	if (!g_shell.is_in_quotes && ((i == 0 && token->type == 6)
			|| (token->type == 6 && !(array + (i - 1))->escapes)))
		g_shell.is_in_s_quotes = !g_shell.is_in_s_quotes;
}

void	need_to_escape(t_token *token, t_ptoken *array, int i)
{
	if (token->id)
		if ((array + (i - 1))->escapes)
			(array + i)->is_escaped = true;
}

void	error_and_bslash(t_token *token, t_ptoken *array, int i)
{
	if (token->type != 3 && (i && !(array + (i - 1))->is_in_quotes))
		g_shell.error = false;
	if (token->type == 3 && !g_shell.is_in_s_quotes)
		(array + i)->str = treat_backslash((array + i));
}

void	check_spaces(t_token *token, t_ptoken *array, int i)
{
	if ((array + i)->is_in_quotes || (array + i)->is_in_squotes)
		(array + i)->spaces = token->spaces;
	else if (token->spaces)
		(array + i)->spaces = 1;
}
