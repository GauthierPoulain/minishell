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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned long	temp;
	char			*substr;

	i = 0;
	temp = 0;
	substr = gc_malloc(sizeof(char) * (len + 1));
	if (!s || !substr)
		return (0);
	while (s[i] && temp < len)
	{
		if (i >= start)
			substr[temp++] = s[i];
		i++;
	}
	substr[temp] = 0;
	return (substr);
}

/*
//	token 0 = arguments
//	token 1 = options
//	token 2 = '$'
*/

void	display_tokens()
{
	t_list	*lst;
	t_token	*token;

	lst = g_shell.tokens;
	while (lst)
	{
		token = (t_token *)lst->content;
		printf("string [%s]\n", token->str);
		printf("type   [%d]\n", token->type);
		printf("id     [%d]\n", token->id);
		lst = lst->next;
	}
}

int	get_token_info(t_token *token, char *line, int start, int end)
{
	token->str = ft_substr(line, start, end - start);
	if (!ft_strcmp(token->str, "-n"))
		token->type = 1;
	else if (token->str[0] == '$')
	{
		if (check_type_at(token->id - 1) == 2)
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

void	get_lexer(char *line)
{
	t_lexer	lexer;
	t_token	*token;

	init_lexer(&lexer);
	while (line[lexer.i])
	{
		token = gc_malloc(sizeof(t_token));
		if (line[lexer.i] == ' ' || (line[lexer.i] == '$' && lexer.i != 0))
		{
			if (line[lexer.i - 1] != ' ')
			{
				token->id = lexer.id++;
				if (get_token_info(token, line, lexer.j, lexer.i) != 2)
					ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
			}
			if (line[lexer.i] == '$')
				lexer.j = lexer.i;
			else
				lexer.j = lexer.i + 1;
		}
		lexer.i++;
	}
	if (ft_strlen(line))
	{
		if (line[lexer.i - 1])
		{
			token->id = lexer.id++;
			if (get_token_info(token, line, lexer.j, lexer.i) != 2)
				ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
		}
	}
	display_tokens();
	// TODO : Delete this, will make us suffer later since we need the list to parse
	ft_lstclear(&g_shell.tokens);
}