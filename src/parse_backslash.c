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

	r_back = (((back / 2) + 1) / 2);
	new = ft_calloc_char(r_back + 1, '\\');
	new = ft_strjoin(new, word + back);
	*i += (((back / 2) + 1) / 2);
	if (back % 4 == 1)
		*trans = 0;
	else if (back % 4 == 2)
		if (word[r_back + 1] == '$')
			return (new);
	return (new);
}

char	*treat_backslash(char *word, int *i, int *trans)
{
	int	back;

	if (*i == 0)
	{
		back = bslash_f_count(word, *i);
		if (back % 2 && ft_strlen(word) == (size_t)back)
		{
			ft_putstr_fd(2, "Syntax error");
			return ("");
		}
		else
			return (bslash_filled(word, i, trans, back));
		*i += back;
		return (ft_strdup(word + 1));
	}
	return (NULL);
}
