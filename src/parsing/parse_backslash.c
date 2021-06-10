#include "../../includes/minishell.h"

static size_t	bslash_f_count(char *word)
{
	int	j;
	int i;

	j = 0;
	i = 0;
	while (word[i] == '\\')
	{
		i++;
		j++;
	}
	return (j);
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
	if (DEBUG)
		printf("back is : %d\n", back);
	if (back % 2 && !g_shell.next_token_str)
		return (error_bslash());
	return (bslash_filled(word, back));
}
