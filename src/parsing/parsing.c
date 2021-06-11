#include "../../includes/minishell.h"

void	chose_parsing(t_ptoken *p_token, t_list *lst)
{
	p_token->str = parse_tokens(lst->content);
	// p_token->str = ((t_token *)lst->content)->str;
}

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
		if (!ft_strcmp((array + i)->str, "\"") && !(array + i)->is_escaped && !(array + i)->is_in_squotes && !(array + (i - 1))->is_in_squotes)
			quotes++;
		i++;
	}
	i = 0;
	while ((array + i)->str)
	{
		if (!ft_strcmp((array + i)->str, "\'") && !(array + i)->is_escaped && !(array + i)->is_in_quotes)
			s_quotes++;
		i++;
	}
	printf("squotes count: %d\nquotes count: %d\n", s_quotes, quotes);
	if (s_quotes % 2 || quotes % 2)
		return (1);
	return (0);
}

// int	count_backslash(t_ptoken *array)
// {
// 	int	i;

// 	i = 0;
// 	while ((array + i)->str)
// 	{
// 		if ((array + i)->str[0] == '\\' && !(array + i)->is_escaped)
// 			(array + i)->str = treat_backslash(array, i);
// 		if (!(array + i)->str)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

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
		token = lst->content;
		do_both(lst, array, i);
		(array + i)->str = token->str;
		if (token->type != 3)
			g_shell.error = false;
		if (token->type == 3)
			(array + i)->str = treat_backslash((array + i));
		if (token->id)
			if ((array + (i - 1))->escapes)
				(array + i)->is_escaped = true;
		if (token->type == 4 || token->type == 6
			|| token->type == 10)
		{
			if ((i == 0 && token->type == 4) || (token->type == 4 && !(array + (i - 1))->escapes))
				g_shell.is_in_quotes = !g_shell.is_in_quotes;
			if ((i == 0 && token->type == 6) || (token->type == 6 && !(array + (i - 1))->escapes))
				g_shell.is_in_s_quotes = !g_shell.is_in_s_quotes;
		}
		printf("Je suis le token [%s]\n", token->str);
		if (g_shell.is_in_quotes)
			(array + i)->is_in_quotes = true;
		else
			(array + i)->is_in_quotes = false;
		if (g_shell.is_in_s_quotes)
			(array + i)->is_in_squotes = true;
		else
			(array + i)->is_in_squotes = false;
		lst = lst->next;
		i++;
	}
	if (g_shell.error)
	{
		printf("error null\n");
		return (NULL);
	}
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
		syntax_error();
		ft_lstclear(&g_shell.tokens);
		return (NULL);
	}
	display_ptoken(array);
	ret = count_quotes(array);
	printf("Quotes nb : %d===========\n", ret);
	if (ret)
	{
		syntax_error();
		clear_ptoken(array);
		ft_lstclear(&g_shell.tokens);
		return (NULL);
	}
	printf("je suis la fin\n");
	// treat_array(array);
	return (array);
}
