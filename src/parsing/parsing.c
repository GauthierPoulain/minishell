#include "../../includes/minishell.h"

void	chose_parsing(t_ptoken *p_token, t_list *lst)
{
	if (((t_token *)lst->content)->type == 4)
		p_token->str = parse_d_quotes(((t_token *)lst->content)->str);
	else if (((t_token *)lst->content)->type == 6)
		p_token->str = parse_s_quotes(((t_token *)lst->content)->str);
	else
	{
		if (DEBUG)
			printf("ALED OUI\n");
		p_token->str = parse_tokens(((t_token *)lst->content)->str);
	}
}

void	join_no_space(t_ptoken *p_tokens, int *i, int *size)
{
	char	*tmp;

	printf("JOINED MA BOI\n");
	tmp = ft_strdup(p_tokens[*i].str);
	(p_tokens + *i)->str = NULL;
	gc_free((p_tokens + *i)->str);
	(p_tokens + (*i - 1))->str = ft_strjoin((p_tokens + (*i - 1))->str, tmp);
	*i -= 1;
	*size -= 1;
}

static void	things(t_list *lst, t_ptoken *p_tokens, int i)
{
	(void)i;
	g_shell.curr_token = (t_token *)lst->content;
	if (lst->next)
		g_shell.next_token_str = ((t_token *)lst->next->content)->str;
	chose_parsing(p_tokens + i, lst);
	g_shell.curr_token = NULL;
	g_shell.next_token_str = NULL;
}

t_ptoken	*array_from_list(void)
{
	int				size;
	int				i;
	t_list			*lst;
	t_ptoken		*array;

	i = 0;
	size = ft_lstsize(g_shell.tokens);
	array = ft_calloc(sizeof(t_ptoken) * (size + 1));
	lst = g_shell.tokens;
	while (i < size && lst && g_shell.error == false)
	{
		(array + i)->is_escaped = false;
		(array + i)->str = NULL;
		things(lst, array, i);
		if (g_shell.error == true)
			return (NULL);
		if (!((t_token *)lst->content)->sp
			&& ((t_token *)lst->content)->id >= 1
			&& check_type_at(i - 1) != 10)
			join_if_needed(array, &i, &size, lst);
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
	// if (P_ARRAY && array)
	// 	display_array(array);
	return (array);
}
