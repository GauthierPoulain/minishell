#include "../includes/minishell.h"

/*
//	token 0 = arguments
//	token 1 = options
//	token 2 = '$'
//	token 3 = '\'
//	token 4 = '"'
*/

int	get_token_info(t_token *token, char *line, int start, int end)
{
	token->str = ft_substr(line, start, end - start);
	if (DEBUG)
		printf("substr :(%d)(%d) [%s]\n", start, end, token->str);
	if (!ft_strcmp(token->str, "-n"))
		token->type = 1;
	else if (token->str[0] == '$')
		return (set_dollar_type(token, line, start));
	else if (token->str[0] == '\\')
		token->type = 3;
	else if (token->str[0] == '"')
		token->type = 4;
	else
		token->type = 0;
	return (0);
}

static int	get_dollar_len(char *line, int i)
{
	int	l;

	l = 0;
	while (line[i] && line[i] != ' ')
	{
		i++;
		l++;
	}
	return (l);
}

void	handle_tokens(char *line, t_token *token, t_lexer *lexer)
{
	int	temp;

	if (line[lexer->i] == ' ' && line[lexer->i - 1] != ' ')
	{
		get_token_info(token, line, lexer->j, lexer->i);
		ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
		lexer->j = lexer->i + 1;
		token->id = lexer->id++;
	}
	else if (line[lexer->i] == '$' && lexer->i != 0)
	{
		if (line[lexer->i - 1] == ' ')
		{
			temp = get_dollar_len(line, lexer->i);
			get_token_info(token, line, lexer->j, lexer->i + temp);
			ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
			token->id = lexer->id++;
			lexer->j = lexer->i + temp + 1;
			lexer->i += temp;
		}
	}
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
	char	*set;

	set = " \\$";
	init_lexer(&lexer);
	printf("len : %zu\n", ft_strlen(line));
	while (lexer.i < (int)ft_strlen(line))
	{
		token = gc_malloc(sizeof(t_token));
		if (ft_ischarset(line[lexer.i], set))
			handle_tokens(line, token, &lexer);
		lexer.i++;
	}
	if (ft_strlen(line) && (int)ft_strlen(line) != lexer.j)
		handle_single_token(line, token, &lexer);
	if (DEBUG)
		display_tokens();
}
