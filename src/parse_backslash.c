#include "../includes/minishell.h"

static size_t	bslash_f_count(char *word, int i)
{
	int	j;

	j = 0;
	while (word[i] == '\\')
	{
		i++;
		j++;
	}
	return (j);
}

char	*bslash_filled(char *word, int *i, int *trans, int back)
{
	char	*new;
	int		r_back;

	r_back = back / 2;
	new = ft_calloc_char(r_back + 1, '\\');
	new = ft_strjoin(new, word + back + *i);
	*i += r_back;
	if (back % 4 == 1 || back % 4 == 3)
		*trans = 1;
	return (new);
}

char	*treat_first_bslash(char *word, int *i, int *trans, int back)
{
	if (back % 2 && ft_strlen(word) == *i + (size_t)back)
	{
		*i = 0;
		ft_putstr_fd(2, "Syntax error");
		ft_lstclear(&g_shell.tokens);
		g_shell.last_return = 1;
		return ("");
	}
	else
		return (bslash_filled(word, i, trans, back));
}

char	*treat_other_bslash(char *word, int *i, int *trans, int back)
{
	if (back % 2 && ft_strlen(word) == (size_t)back + *i)
	{
		*i = 0;
		ft_putstr_fd(2, "Syntax error");
		ft_lstclear(&g_shell.tokens);
		g_shell.last_return = 1;
		return ("");
	}
	return (ft_strjoin(ft_strndup(word, *i),
			bslash_filled(word, i, trans, back)));
}

char	*treat_backslash(char *word, int *i, int *trans)
{
	int		back;

	back = bslash_f_count(word, *i);
	if (*i == 0)
		return (treat_first_bslash(word, i, trans, back));
	else
		return (treat_other_bslash(word, i, trans, back));
}
