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

/*
//	token 0 = arguments
//	token 1 = options
//	token 2 = '$'
*/

int	get_token_info(t_token *token, char *line, int start, int end)
{
	token->str = ft_substr(line, start, end - start);
	printf("substr :(%d)(%d) [%s]\n", start, end, token->str);
	if (!ft_strcmp(token->str, "-n"))
		token->type = 1;
	else if (token->str[0] == '$')
	{
		if (check_type_at(token->id - 1) == 2 && line[start - 1] != ' ')
		{
			join_last_token(token);
			printf("Last type is [%d]\n", check_type_at(token->id - 1));
			token->type = 2;
			return (2);
		}
		token->type = 2;
	}
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

// static int	len_to_charset(char *line, int i, char *set)
// {
// 	int	l;

// 	l = 0;
// 	while (line[i])
// 	{
// 		if (ft_ischarset(line[i], set))
// 			return (l);
// 		i++;
// 		l++;
// 	}
// 	return (0);
// }

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
			lexer->j = lexer->i + temp;
			lexer->i += temp + 1;
			printf("lexer i during : %d\n", lexer->i);
		}
	}
	// printf("salut [%s]\n", token->str);
}

void	handle_single_token(char *line, t_token *token, t_lexer *lexer)
{
	printf("secondary\n");
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

	set = " $";
	init_lexer(&lexer);
	printf("len : %zu\n", ft_strlen(line));
	while (lexer.i < (int)ft_strlen(line))
	{
		token = gc_malloc(sizeof(t_token));
		if (ft_ischarset(line[lexer.i], set))
			handle_tokens(line, token, &lexer);
		lexer.i++;
		printf("lexer i : %d\n", lexer.i);
	}
	if (ft_strlen(line) && (int)ft_strlen(line) != lexer.j)
		handle_single_token(line, token, &lexer);
	display_tokens();
}
