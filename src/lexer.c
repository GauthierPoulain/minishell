#include "../includes/minishell.h"

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
//	token 1 = commands
//	token 2 = options
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

void	get_token_info(t_token *token, char *line, int start, int end)
{
	token->str = ft_substr(line, start, end - start);
	if (token->id == 0)
		token->type = 1;
	else if (!ft_strcmp(token->str, "-n"))
		token->type = 2;
	else
		token->type = 0;
}

void	get_lexer(char *line)
{
	int		i;
	int		j;
	int		id;
	t_token	*token;

	i = 0;
	j = 0;
	id = 0;
	while (line[i])
	{
		token = gc_malloc(sizeof(t_token));
		if ((line[i] == ' ' && line[i + 1] != ' ')|| line[i] == '$')
		{
			token->id = id++;
			get_token_info(token, line, j, i);
			ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
			j = i + 1;
		}
		i++;
	}
	if (ft_strlen(line))
	{
		if (line[i - 1])
		{
			token->id = id++;
			get_token_info(token, line, j, i);
			ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
		}
	}
	display_tokens();
	// gc_free(token);
}