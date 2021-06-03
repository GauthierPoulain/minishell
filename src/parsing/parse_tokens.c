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
		ft_putstr_fd(STDERR_FILENO, "Syntax error iiiii\n");
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
		if (new[i] == '\\')
			new = treat_backslash(new, &i);
		printf("actual new [%s] and i : %d\n", new, i);
		if (new[i] == '$')
			new = treat_doll(new, &i);
		if (new[i] == '\"')
			treat_quotes(new, &i);
		if ((new[i] && new[i] != '$')
			|| (new[i] && new[i] == '$' && new[i + 1] == '/'))
			i++;
		g_shell.had_bslash = false;
	}
	return (word);
}
