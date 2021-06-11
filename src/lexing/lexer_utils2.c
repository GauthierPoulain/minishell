#include "../../includes/minishell.h"

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

/*
//alors le == en != est ok tier mais j'ai peur que ça pète autre chose :)
*/

int	bslash_token_len(char *line, t_lexer *lexer)
{
	int		i;
	t_infos	infos;

	infos.was_quotes = false;
	infos.len = 1;
	i = lexer->i + 1;
	no_room_infos(line, &i, &infos);
	while (line[i] && line[i] == '\\')
	{
		i++;
		infos.len++;
	}
	return (infos.len);
}

int	s_quotes_len(char *line, t_lexer *lexer)
{
	int	len;
	int	i;

	len = 1;
	i = lexer->i + 1;
	while (line[i] == '\'')
	{
		i++;
		len++;
	}
	while (line[i])
	{
		if (line[i] == '\'' && line[i + 1] != '\'')
			return (len + 1);
		i++;
		len++;
	}
	return (-1);
}

int	get_token_len(char *line, t_lexer *lexer)
{
	int		i;
	bool	print;

	print = true;
	i = lexer->i;
	if (line[i] == '\"')
	{
		lexer->had_quotes = true;
		return (1);
	}
	else if (line[i] == '\'')
	{
		lexer->had_squotes = true;
		return (1);
	}
	else if (line[i] == '\\')
		return (bslash_token_len(line, lexer));
	else if (line[i] == '>' || line[i] == '|' || line[i] == '<')
	{
		lexer->had_semi = true;
		return (1);
	}
	return (else_token_l(line, lexer));
}

void	token_l_error(char *line, t_lexer *lexer)
{
	ft_putstr_fd(STDERR_FILENO, "Syntax error tokenl\n");
	ft_lstclear(&g_shell.tokens);
	lexer->i = ft_strlen(line);
	g_shell.error = true;
	g_shell.last_return = 2;
	return ;
}
