#include "../../includes/minishell.h"

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

char	*treat_backslash(char *word, int *i, int *trans)
{
	int		back;

	back = bslash_f_count(word, *i);
	printf("back is : %d\n", back);
	if (back % 2 && ft_strlen(word) == *i + (size_t)back && !g_shell.next_token_str)
		return (error_bslash(i));
	if (*i == 0)
		return (bslash_filled(word, i, trans, back));
	else
		return (ft_strjoin(ft_strndup(word, *i),
				bslash_filled(word, i, trans, back)));
}
