#include "../../includes/minishell.h"

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

static void	join_test(t_ptoken *array, int *i, int *size)
{
	char	*buf;

	buf = ft_strdup((array + *i)->str);
	(array + *i)->str = NULL;
	(array + (*i - 1))->str = ft_strjoin((array + (*i - 1))->str, buf);
	swap_rest(array, *i + 1, *size);
}

void	treat_array(t_ptoken *array)
{
	int		i;
	int		size;

	size = get_array_size(array);
	printf("size %d\n", size);
	i = 0;
	while (i < size)
	{
		printf("yo\n");
		if (!(array + i)->is_escaped && !ft_strcmp((array + i)->str, "\"")
			&& i > 1)
		{
			printf("SWAP\n");
			(array + i)->str = NULL;
			swap_rest(array, i + 1, size);
			join_test(array, &i, &size);
			display_ptoken(array);
			i = 0;
		}
		i++;
	}
}

void	clear_ptoken(t_ptoken *array)
{
	int	i;

	i = 0;
	while ((array + i)->str)
	{
		(array + i)->is_escaped = false;
		(array + i)->need_join = false;
		(array + i)->is_in_squotes = false;
		(array + i)->is_in_quotes = false;
		(array + i)->str = NULL;
		gc_free((array + i)->str);
		i++;
	}
	gc_free((array + i));
}
