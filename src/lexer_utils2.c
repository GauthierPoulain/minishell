#include "../includes/minishell.h"

int	quotes_token_len(char *line, t_lexer *lexer)
{
	int	len;
	int	i;

	len = 1;
	i = lexer->i + 1;
	while (line[i] == '"')
	{
		i++;
		len++;
	}
	while (line[i])
	{
		if (line[i] == '"' && line[i + 1] != '"')
		{
			lexer->had_quotes = true;
			return (len + 1);
		}
		i++;
		len++;
	}
	return (-1);
}

int	bslash_token_len(char *line, t_lexer *lexer)
{
	int	len;
	int	i;

	len = 1;
	i = lexer->i + 1;
	if (line[i] == '\"' || line[i] == '\"')
	{
		i++;
		len++;
	}
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '"')
			return (len);
		i++;
		len++;
	}
	return (len);
}

int	get_token_len(char *line, t_lexer *lexer)
{
	int	len;
	int	i;

	len = 0;
	i = lexer->i;
	if (line[i] == '"')
		return (quotes_token_len(line, lexer));
	else if (line[i] == '\\')
		return (bslash_token_len(line, lexer));
	return (else_token_l(line, lexer));
}

void	token_l_error(char *line, t_lexer *lexer)
{
	ft_putstr_fd(2, "Syntax error\n");
	ft_lstclear(&g_shell.tokens);
	lexer->i = ft_strlen(line);
	g_shell.last_return = 1;
	return ;
}
