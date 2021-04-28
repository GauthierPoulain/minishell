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
		lst = lst->next;
	}
}

void	get_token_info(t_token *token, char *line, int start, int end)
{
	token->str = ft_substr(line, start, end - start);
	printf("(%s)\n", token->str);
	if (!ft_strcmp(token->str, "echo") || !ft_strcmp(token->str, "cd") || !ft_strcmp(token->str, "pwd")
			|| !ft_strcmp(token->str, "export") || !ft_strcmp(token->str, "unset") || !ft_strcmp(token->str, "env")
				|| !ft_strcmp(token->str, "exit"))
		token->type = 1;
	if (!ft_strcmp(token->str, "-n"))
		token->type = 2;
	else
		token->type = 0;
}

void	get_lexer(char *line)
{
	int		i;
	int		j;
	t_token	*token;

	i = 0;
	j = 0;
	while (line[i])
	{
		token = gc_malloc(sizeof(t_token));
		if ((line[i] == ' ' && line[i + 1] != ' ')|| line[i] == '$')
		{
			get_token_info(token, line, j, i);
			ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
			j = i;
		}
		i++;
	}
	get_token_info(token, line, j, i);
	ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
	display_tokens();
	// gc_free(token);
}