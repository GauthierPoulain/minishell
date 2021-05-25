#include "../includes/minishell.h"

int	quotes_token_len(char *line, t_lexer *lexer)
{
	int	len;
	int	i;

	len = 1;
	i = lexer->i + 1;
	if (DEBUG)
		printf("quotes token\n");
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
	// if (lexer->had_bslash)
	// 	return (len + 1);
	return (-1);
}

int	bslash_token_len(char *line, t_lexer *lexer)
{
	int	len;
	int	i;

	len = 1;
	i = lexer->i + 1;
	if (DEBUG)
		printf("blash token\n");
	if (line[i] == '\"')
	{
		i++;
		len++;
	}
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '"')
		{
			if (i && line[i - 1] == '\\')
			{
				lexer->had_bslash = true;
				printf("blash status : [%d]\n", lexer->had_bslash);
				return (len - 1);
			}
			return (len);
		}
		i++;
		len++;
	}
	return (len);
}

int	get_token_len(char *line, t_lexer *lexer)
{
	int	i;

	i = lexer->i;
	if (DEBUG)
		printf("actual char [%c] during line [%s]\n", line[i], line + i);
	if (line[i] == '\"')
		return (quotes_token_len(line, lexer));
	else if (line[i] == '\\')
		return (bslash_token_len(line, lexer));
	return (else_token_l(line, lexer));
}

void	token_l_error(char *line, t_lexer *lexer)
{
	ft_putstr_fd(2, "Syntax error");
	ft_lstclear(&g_shell.tokens);
	lexer->i = ft_strlen(line);
	g_shell.error = true;
	g_shell.last_return = 1;
	return ;
}
