#include "../../includes/minishell.h"

void	chose_parsing(t_ptoken *p_token, t_list *lst)
{
	if (DEBUG)
		printf("ALED OUI\n");
	p_token->str = parse_tokens(lst->content);
	printf("token during parsing %s\n", p_token->str);
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
	int	count;

	i = 0;
	count = 0;
	while ((array + i)->str)
	{
		printf("During count : [%s]\n", (array + i)->str);
		if (!ft_strcmp((array + i)->str, "\"") && !(array + i)->is_escaped)
			count++;
		i++;
	}
	return (count);
}

t_ptoken	*array_from_list(void)
{
	int				size;
	int				i;
	t_list			*lst;
	t_ptoken		*array;

	init_things(&size, &i);
	array = ft_calloc(sizeof(t_ptoken) * (size + 1));
	lst = g_shell.tokens;
	while (i < size && lst && g_shell.error == false)
	{
		if (do_both(lst, array, i))
			return (NULL);
		if (check_things(lst))
		{
			if (!(array + (i - 1))->is_escaped
				&& get_token_at(((t_token *)lst->content)->id - 1)->type != 10
				&& get_token_at(((t_token *)lst->content)->id - 1)->type != 4)
				join_if_needed(array, &i, &size, lst);
			else if ((array + (i - 1))->is_escaped)
				join_if_needed(array, &i, &size, lst);
		}
		if (g_shell.is_in_quotes)
			(array + i)->is_in_quotes = true;
		else
			(array + i)->is_in_quotes = false;
		lst = lst->next;
		i++;
	}
	return (array);
}

t_ptoken	*parse_line(char *line)
{
	t_ptoken	*array;
	int			nb;

	get_lexer(line);
	g_shell.error = false;
	g_shell.is_in_quotes = false;
	g_shell.is_in_s_quotes = false;
	array = array_from_list();
	nb = count_quotes(array); 
	display_ptoken(array);
	printf("Quotes nb : %d===========\n", nb);
	if (count_quotes(array) % 2)
	{
		syntax_error();
		clear_ptoken(array);
		ft_lstclear(&g_shell.tokens);
		return (NULL);
	}
	// treat_array(array);
	return (array);
}
