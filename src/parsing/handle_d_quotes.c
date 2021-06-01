#include "../../includes/minishell.h"

static char	*count_and_trim(char *word, size_t size)
{
	int	first;
	int	lasts;

	first = 0;
	lasts = 0;
	g_shell.is_in_quotes = true;
	while (word[first] == '\"')
		first++;
	while (word[--size] == '\"')
		lasts++;
	if (first != lasts && !g_shell.had_bslash)
	{
		ft_putstr_fd(2, "Syntax error\n");
		ft_lstclear(&g_shell.tokens);
		g_shell.last_return = 1;
		return (NULL);
	}
	word = ft_substr(word, first, size + 1 - lasts);
	word = parse_tokens(word);
	g_shell.is_in_quotes = false;
	return (word);
}

char	*parse_d_quotes(char *word)
{
	word = count_and_trim(word, ft_strlen(word));
	return (word);
}
