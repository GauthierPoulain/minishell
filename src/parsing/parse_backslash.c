#include "../../includes/minishell.h"

static size_t	bslash_f_count(char *word)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (word[i] == '\\')
	{
		count++;
		i++;
	}
	return (count);
}

char	*special_trim_quotes(char *word)
{
	int		first;
	int		lasts;
	int		size;
	char	*new;

	first = 0;
	lasts = 0;
	size = ft_strlen(word);
	while (word[first] == '\"')
		first++;
	while (word[--size] == '\"')
		lasts++;
	new = ft_substr(word, first, size + 2 - lasts);
	return (new);
}

char	*treat_backslash(t_ptoken *word)
{
	int		back;

	back = bslash_f_count(word->str);
	if (back % 2)
	{
		if (!word->is_in_quotes && !word->is_in_squotes)
			word->escapes = true;
		g_shell.error = true;
	}
	return (bslash_filled((word), back));
}
