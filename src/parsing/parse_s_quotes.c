#include "../../includes/minishell.h"

static char	*trim_s_quotes(t_ptoken *word, size_t size)
{
	int	first;
	int	lasts;

	first = 0;
	lasts = 0;
	g_shell.is_in_s_quotes = true;
	while (word->str[first] == '\'')
		first++;
	while (word->str[--size] == '\'')
		lasts++;
	if (first != lasts)
	{
		ft_putstr_fd(STDERR_FILENO, "Syntax error quotes\n");
		ft_lstclear(&g_shell.tokens);
		g_shell.last_return = 2;
		return (NULL);
	}
	word->str = ft_substr(word->str, first, size + 1 - lasts);
	word->str = parse_tokens(word);
	g_shell.is_in_s_quotes = false;
	return (word->str);
}

char	*parse_s_quotes(t_ptoken *word)
{
	return (trim_s_quotes(word, ft_strlen(word->str)));
}
