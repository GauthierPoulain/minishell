#include "../../includes/minishell.h"

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
	if (DEBUG)
		printf("blash token\n[%s]\n", line + i);
	no_room_infos(line, &i, &infos);
	if (DEBUG)
		printf("line bslash [%s]\n", line + i);
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
	if (DEBUG)
		printf("squotes\n");
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
	if (print && DEBUG)
		printf("actual char [%c] during line [%s]\n", line[i], line + i);
	if (line[i] == '\"')
		return (quotes_token_len(line, lexer));
	else if (line[i] == '\'')
		return (s_quotes_len(line, lexer));
	else if (line[i] == '\\')
		return (bslash_token_len(line, lexer));
	else if (line[i] == '>' || line[i] == '|' || line[i] == '<')
	{
		lexer->had_semi = true;
		return (is_operator(line + lexer->i));
	}
	return (else_token_l(line, lexer));
}

void	token_l_error(char *line, t_lexer *lexer)
{
	if (DEBUG)
		printf("tokenl\n");
	ft_putstr_fd(STDERR_FILENO, "Syntax error tokenl\n");
	ft_lstclear(&g_shell.tokens);
	lexer->i = ft_strlen(line);
	g_shell.error = true;
	g_shell.last_return = 2;
	return ;
}
