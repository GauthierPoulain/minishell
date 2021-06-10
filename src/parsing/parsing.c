#include "../../includes/minishell.h"

void	display_ptoken(t_ptoken *array)
{
	int	i;

	i = 0;
	while ((array + i)->str)
	{
		printf("(%s)\n", (array + i)->str);
		i++;
	}
}

void	chose_parsing(t_ptoken *p_token, t_list *lst)
{
	// if (((t_token *)lst->content)->type == 4)
	// 	p_token->str = parse_d_quotes(((t_token *)lst->content)->str);
	// if (((t_token *)lst->content)->type == 6)
	// 	p_token->str = parse_s_quotes(((t_token *)lst->content)->str);
	if (DEBUG)
		printf("ALED OUI\n");
	p_token->str = parse_tokens(lst->content);
	printf("token during parsing %s\n", p_token->str);
}

void	join_no_space(t_ptoken *p_tokens, int *i, int *size)
{
	char	*tmp;

	printf("JOINED MA BOI\n");
	tmp = ft_strdup((p_tokens + *i)->str);
	(p_tokens + *i)->str = NULL;
	gc_free((p_tokens + *i)->str);
	(p_tokens + (*i - 1))->str = ft_strjoin((p_tokens + (*i - 1))->str, tmp);
	*i -= 1;
	*size -= 1;
}

void	things(t_list *lst, t_ptoken *p_tokens, int i)
{
	g_shell.curr_token = (t_token *)lst->content;
	if (lst->next)
		g_shell.next_token_str = ((t_token *)lst->next->content)->str;
	chose_parsing(p_tokens + i, lst);
	g_shell.curr_token = NULL;
	g_shell.next_token_str = NULL;
}

void	swap_rest(t_ptoken *array, int i)
{
	while ((array + i)->str)
	{
		ft_swap((array + i), (array + (i - 1)));
		i++;
	}
}

void	treat_array(t_ptoken *array)
{
	int		i;
	int		size;
	// char	*buf;

	size = 0;
	i = 0;
	while ((array + i)->str)
	{
		size++;
		i++;
	}
	i = 0;
	while (i < size)
	{
		printf("yo\n");
		if (!(array + i)->is_escaped && !ft_strcmp((array + i)->str, "\""))
		{
			printf("SWAP\n");
			(array + i)->str = NULL;
			swap_rest(array, i + 1);
		}
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
	display_ptoken(array);
	treat_array(array);
	display_ptoken(array);
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
	return (array);
}
