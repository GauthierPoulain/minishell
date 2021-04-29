#include "../includes/minishell.h"

void	init_lexer(t_lexer *lexer)
{
	lexer->i = 0;
	lexer->j = 0;
	lexer->id = 0;
}

int	check_type_at(int i)
{
	t_list	*lst;
	t_token	*token;

	lst = g_shell.tokens;
	while (lst)
	{
		token = lst->content;
		if (token->id == i)
			return (token->type);
		lst = lst->next;
	}
	return (-1);
}
