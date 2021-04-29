#include "../includes/minishell.h"

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

/*
//	token 0 = arguments
//	token 1 = options
//	token 2 = '$'
*/

int	get_token_info(t_token *token, char *line, int start, int end)
{
	token->str = ft_substr(line, start, end - start);
	if (!ft_strcmp(token->str, "-n"))
		token->type = 1;
	else if (token->str[0] == '$')
	{
		if (check_type_at(token->id - 1) == 2 && line[start - 1] != ' ')
		{
			join_last_token(token);
			printf("Last type is [%d]\n", check_type_at(token->id - 1));
			token->type = 2;
			return(2);
		}
		token->type = 2;
	}
	else
		token->type = 0;
	return (0);
}

void	handle_tokens(char *line, t_token *token, t_lexer *lexer)
{
	if (line[lexer->i - 1] != ' ')
	{
		token->id = lexer->id++;
		if (get_token_info(token, line, lexer->j, lexer->i) != 2)
			ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
	}
	if (line[lexer->i] == '$')
		lexer->j = lexer->i;
	else
		lexer->j = lexer->i + 1;
}

void	handle_single_token(char *line, t_token *token, t_lexer *lexer)
{
	if (line[lexer->i - 1])
	{
		token->id = lexer->id++;
		if (get_token_info(token, line, lexer->j, lexer->i) != 2)
			ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
	}
}

void	get_lexer(char *line)
{
	t_lexer	lexer;
	t_token	*token;

	init_lexer(&lexer);
	while (line[lexer.i])
	{
		token = gc_malloc(sizeof(t_token));
		if (line[lexer.i] == ' ' || (line[lexer.i] == '$' && lexer.i != 0))
			handle_tokens(line, token, &lexer);
		lexer.i++;
	}
	if (ft_strlen(line))
		handle_single_token(line, token, &lexer);
	display_tokens();
	// TODO : Delete this, will make us suffer later since we need the list to parse
	ft_lstclear(&g_shell.tokens);
}