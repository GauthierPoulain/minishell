#include "../includes/minishell.h"

size_t	bslash_f_count(char *word, int i)
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

static int	real_bslash(int nb)
{
	if (nb % 2)
		return (0);
	return (((nb / 2) + 1) / 2);
}

char	*treat_backslash(char *word, int *i)
{
	char	*new;

	int	back;
	if (*i == 0)
	{
		back = bslash_f_count(word, *i);
		if (back % 2)
		{
			ft_putstr_fd(2, "Syntax error");
			return ("");
		}
		else
		{
			new = ft_calloc_char((real_bslash(back)) + 1, '\\');
			new = ft_strjoin(new, word + back);
			*i += real_bslash(back);
			return (new);
		}
		*i += back;
		return (ft_strdup(word + 1));
	}
	return (NULL);
}
