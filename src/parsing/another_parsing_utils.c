#include "../../includes/minishell.h"

void	join_no_space(t_ptoken *p_tokens, int *i, int *size)
{
	char	*tmp;

	tmp = ft_strdup((p_tokens + *i)->str);
	(p_tokens + *i)->str = NULL;
	gc_free((p_tokens + *i)->str);
	(p_tokens + (*i - 1))->str = ft_strjoin((p_tokens + (*i - 1))->str, tmp);
	*i -= 1;
	*size -= 1;
}

static void	join_test(t_ptoken *array, int *i, int *size)
{
	char	*buf;

	buf = ft_strdup((array + *i)->str);
	(array + *i)->str = ft_strdup("");
	(array + (*i - 1))->str = ft_strjoin((array + (*i - 1))->str, buf);
	swap_rest(array, *i + 1, *size);
}

void	treat_array(t_ptoken *array)
{
	int		i;
	int		size;

	size = get_array_size(array);
	i = 0;
	while (i < size)
	{
		if (!(array + i)->is_escaped && !ft_strcmp((array + i)->str, "\"")
			&& i > 1)
		{
			if (DEBUG)
				printf("SWAP\n");
			(array + i)->str = ft_strdup("");
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
