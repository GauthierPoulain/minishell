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

int bslash_token_len(char *line, t_lexer *lexer)
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