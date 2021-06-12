#include "../../includes/minishell.h"

/*
//	token 0 = arguments
//	token 1 = options
//	token 2 = $
//	token 3 = \
//	token 4 = "
//	token 5 = /
//	token 6 = '
//	token 10 = ;
*/

static int	get_token_info(t_token *token, char *line, int start, int end)
{
	token->str = ft_substr(line, start, end - start);
	if (!ft_strcmp(token->str, "-n"))
		token->type = 1;
	else if (token->str[0] == '\\')
		token->type = 3;
	else if (token->str[0] == '"')
		token->type = 4;
	else if (token->str[0] == '/')
		token->type = 5;
	else if (token->str[0] == '\'')
		token->type = 6;
	else if (ft_ischarset(token->str[0], ";>|<"))
		token->type = 10;
	else
		token->type = 0;
	return (0);
}

int	else_token_l(char *line, t_lexer *lexer)
{
	int	len;
	int	i;

	len = 0;
	i = lexer->i;
	while (line[i])
	{
		if (ft_isspace(line[i]) || ft_ischarset(line[i], ";><|\"\'\\"))
		{
			if (line[i] == ';')
				lexer->had_semi = true;
			if (len == 0 && line[i] == ';')
				len++;
			return (len);
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	handle_space(char *line, t_token *token, t_lexer *lexer)
{
	int		token_l;

	lexer->had_semi = false;
	if (lexer->had_quotes)
		lexer->had_quotes = false;
	token->spaces = 0;
	while (ft_isspace(line[lexer->i]))
	{
		token->spaces++;
		lexer->i++;
	}
	token_l = get_token_len(line, lexer);
	if (token_l == -1)
		return (token_l_error(line, lexer));
	token->id = lexer->id++;
	get_token_info(token, line, lexer->i, lexer->i + token_l);
	ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
	lexer->i += token_l;
	if (lexer->i > (int)ft_strlen(line))
		lexer->i = ft_strlen(line);
}

static int	normed_condition(t_lexer lexer, char *line)
{
	return (ft_isspace(line[lexer.i]) || line[lexer.i] == '\\'
		|| lexer.i == 0 || line[lexer.i] == '"'
		|| lexer.had_quotes || lexer.had_squotes
		|| line[lexer.i] == '\'' || (lexer.i && line[lexer.i - 1] == '\\')
		|| line[lexer.i] == ';' || line[lexer.i] == '>' || lexer.had_semi
		|| line[lexer.i] == '|' || line[lexer.i] == '<');
}

void	get_lexer(char *line)
{
	t_lexer	lexer;
	t_token	*token;

	init_lexer(&lexer);
	while (lexer.i < (int)ft_strlen(line))
	{
		token = gc_malloc(sizeof(t_token));
		if (normed_condition(lexer, line))
			handle_space(line, token, &lexer);
		if (!ft_isspace(line[lexer.i]) && line[lexer.i] != '"'
			&& line[lexer.i] != '\\' && !lexer.had_quotes
			&& line[lexer.i] != '\'' && line[lexer.i - 1] != '\\'
			&& line[lexer.i] != ';' && !lexer.had_semi
			&& line[lexer.i] != '>' && line[lexer.i] != '|'
			&& line[lexer.i] != '<' && !lexer.had_squotes)
			lexer.i++;
	}
	if (DEBUG)
		display_tokens();
}
