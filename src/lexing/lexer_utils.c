#include "../../includes/minishell.h"

void	init_lexer(t_lexer *lexer)
{
	lexer->i = 0;
	lexer->j = 0;
	lexer->id = 0;
	lexer->had_quotes = false;
	lexer->had_semi = false;
}

t_token	*get_token_at(int i)
{
	t_list	*lst;
	t_token	*token;

	lst = g_shell.tokens;
	while (lst)
	{
		token = lst->content;
		if (token->id == i)
			return (token);
		lst = lst->next;
	}
	return (NULL);
}

void	display_tokens(void)
{
	t_list	*lst;
	t_token	*token;

	lst = g_shell.tokens;
	while (lst)
	{
		token = (t_token *)lst->content;
		printf("string [%s]\n", token->str);
		printf("space  [%d]\n", token->spaces);
		printf("type   [%d]\n", token->type);
		printf("id     [%d]\n", token->id);
		lst = lst->next;
	}
}

void	join_last_token(t_token *token)
{
	t_list	*lst;
	t_token	*actual;

	lst = g_shell.tokens;
	while (lst)
	{
		actual = lst->content;
		if (actual->id == token->id - 1)
			actual->str = ft_strjoin(actual->str, token->str);
		lst = lst->next;
	}
}

int	set_dollar_type(t_token *token, char *line, int start)
{
	if (get_token_at(token->id - 1)->type == 2 && !ft_isspace(line[start - 1]))
	{
		join_last_token(token);
		token->type = 2;
		return (2);
	}
	token->type = 2;
	return (0);
}
