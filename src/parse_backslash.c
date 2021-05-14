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

char	*treat_backslash(char *word, int *i)
{
	// char	*new;
	if (*i == 0)
	{
		if (bslash_f_count(word, *i))
		{
			ft_putstr_fd(2, "Syntax error");
			return ("");
		}
		*i += 1;
		return (ft_strdup(word + 1));
	}
	return (NULL);
}
