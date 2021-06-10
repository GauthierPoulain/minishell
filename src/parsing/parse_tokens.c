#include "../../includes/minishell.h"

int	check_slash(t_ptoken *word, int i)
{
	int	j;

	j = i;
	while (word->str[i])
	{
		if (word->str[i] == '$')
			return (0);
		else if (word->str[i] == '/')
			return (i - j);
		i++;
	}
	return (0);
}

char	*treat_quotes(t_ptoken *word, int *i)
{
	int	first;
	int	lasts;
	int	size;

	first = 0;
	lasts = 0;
	size = ft_strlen(word->str + *i);
	while (word->str[*i] == '\"')
	{
		*i += 1;
		first++;
	}
	while (word->str[--size] == '\"')
		lasts++;
	if (first != lasts)
	{
		ft_putstr_fd(STDERR_FILENO, "Syntax error QUOTES\n");
		ft_lstclear(&g_shell.tokens);
		g_shell.last_return = 2;
		return (NULL);
	}
	word->str = ft_substr(word->str, first, size + 1 - lasts);
	word->str = parse_tokens(word);
	return (word->str);
}

char	*parse_tokens(t_ptoken *word)
{
	int		i;
	char	*new;

	i = 0;
	new = word->str;
	while (new[i])
	{
		if (new[i] == '\\')
			new = treat_backslash(word, &i);
		if (DEBUG)
			printf("actual new [%s] and i : %d\n", new, i);
		if ((new[i] && new[i] != '$')
			|| (new[i] && new[i] == '$' && new[i + 1] == '/'))
			i++;
		g_shell.had_bslash = false;
	}
	return (new);
}
