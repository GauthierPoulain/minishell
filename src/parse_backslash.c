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

char	*treat_backslash(char *word, int *i, int *trans)
{
	int		back;
	char	*new;

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
	}
	else
	{
		back = bslash_f_count(word, *i);
		new = ft_strndup(word, *i);
		new = ft_strjoin(new, bslash_filled(word, i, trans, back));
		return (new);
	}
	return (NULL);
}
