#include "../../includes/minishell.h"

int	check_slash(char *word, int i)
{
	int	j;

	j = i;
	while (word[i])
	{
		if (word[i] == '$')
			return (0);
		else if (word[i] == '/')
			return (i - j);
		i++;
	}
	return (0);
}

char	*treat_quotes(char *word, int *i)
{
	int	first;
	int	lasts;
	int	size;

	first = 0;
	lasts = 0;
	size = ft_strlen(word + *i);
	while (word[*i] == '\"')
	{
		*i += 1;
		first++;
	}
	while (word[--size] == '\"')
		lasts++;
	if (first != lasts)
	{
		ft_putstr_fd(2, "Syntax error iiiii\n");
		ft_lstclear(&g_shell.tokens);
		g_shell.last_return = 1;
		return (NULL);
	}
	word = ft_substr(word, first, size + 1 - lasts);
	word = parse_tokens(word);
	return (word);
}

char	*parse_tokens(char *word)
{
	int		i;
	int		trans;

	i = 0;
	trans = 0;
	while (word[i])
	{
		if (word[i] == '\\')
			word = treat_backslash(word, &i, &trans);
		printf("actual word [%s] and i : %d\n also strlen %zu\n", word, i, ft_strlen(word));
		if (word[i] && word[i] == '$')
			word = treat_doll(word, &i, &trans);
		if (word[i] == '\"' && !g_shell.had_bslash)
			treat_quotes(word, &i);
		if ((word[i] && word[i] != '$')
			|| (word[i] && word[i] == '$' && word[i + 1] == '/'))
			i++;
	}
	return (word);
}
