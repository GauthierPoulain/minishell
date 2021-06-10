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
		lst = lst->next;
		i++;
	}
	return (array);
}

t_ptoken	*parse_line(char *line)
{
	t_ptoken	*array;

	get_lexer(line);
	g_shell.error = false;
	g_shell.is_in_quotes = false;
	g_shell.is_in_s_quotes = false;
	array = array_from_list();
	treat_array(array);
	return (array);
}
