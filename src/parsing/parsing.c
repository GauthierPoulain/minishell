#include "../../includes/minishell.h"

void	swap_rest(t_ptoken *array, int i, int size)
{
	while (i < size)
	{
		ft_swap((array + i), (array + (i - 1)));
		i++;
	}
}

int	count_quotes(t_ptoken *array)
{
	int	i;
	int	quotes;
	int	s_quotes;

	i = 0;
	quotes = 0;
	s_quotes = 0;
	while ((array + i)->str)
	{
		printf("sq %d, dq %d, %s\n", (array + i)->is_in_squotes,
			(array + i)->is_in_quotes, (array + i)->str);
		if (!ft_strcmp((array + i)->str, "\""))
		{
			if (!(array + i)->is_in_squotes && !(array + i)->is_escaped)
				quotes++;
		}
		else if (!ft_strcmp((array + i)->str, "\'"))
		{
			if (!(array + i)->is_in_quotes && !(array + i)->is_escaped)
				s_quotes++;
		}
		i++;
	}
	printf("squotes count: %d\nquotes count: %d\n", s_quotes, quotes);
	return (s_quotes % 2 || quotes % 2);
}

t_ptoken	*array_from_list(void)
{
	int				size;
	int				i;
	t_list			*lst;
	t_ptoken		*array;
	t_token			*token;

	init_things(&size, &i);
	array = ft_calloc(sizeof(t_ptoken) * (size + 1));
	lst = g_shell.tokens;
	while (i < size && lst)
	{
		token = init_ptoken(token, lst, array, i);
		check_spaces(token, array, i);
		error_and_bslash(token, array, i);
		need_to_escape(token, array, i);
		if (token->type == 4 || token->type == 6)
			reset_g_shell(i, token, array);
		if (token->type == 0 && i && get_token_at(token->id - 1)->type == 3)
			g_shell.error = false;
		lst = lst->next;
		i++;
	}
	if (g_shell.error)
		return (NULL);
	return (array);
}

t_ptoken	*parse_line(char *line)
{
	t_ptoken	*array;
	int			ret;

	get_lexer(line);
	g_shell.error = false;
	g_shell.is_in_quotes = false;
	g_shell.is_in_s_quotes = false;
	array = array_from_list();
	if (!array)
	{
		g_shell.last_return = syntax_error();
		ft_lstclear(&g_shell.tokens);
		return (NULL);
	}
	printf("je crash la");
	display_ptoken(array);
	ret = count_quotes(array);
	if (ret)
	{
		g_shell.last_return = syntax_error();
		clear_ptoken(array);
		ft_lstclear(&g_shell.tokens);
		return (NULL);
	}
	return (array);
}
