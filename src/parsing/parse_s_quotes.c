#include "../../includes/minishell.h"

static char	*trim_s_quotes(char *word, size_t size)
{
	int	first;
	int	lasts;

	first = 0;
	lasts = 0;
	g_shell.is_in_s_quotes = true;
	while (word[first] == '\'')
		first++;
	while (word[--size] == '\'')
		lasts++;
	if (first != lasts)
	{
		ft_putstr_fd(STDERR_FILENO, "Syntax error\n");
		ft_lstclear(&g_shell.tokens);
		g_shell.last_return = 1;
		return (NULL);
	}
	word = ft_substr(word, first, size + 1 - lasts);
	word = parse_tokens(word);
	g_shell.is_in_s_quotes = false;
	return (word);
}

char	*parse_s_quotes(char *word)
{
	return (trim_s_quotes(word, ft_strlen(word)));
}
