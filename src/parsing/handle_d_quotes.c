#include "../../includes/minishell.h"

static char	*count_and_trim(t_ptoken *word, size_t size)
{
	int	first;
	int	lasts;

	first = 0;
	lasts = 0;
	while (word->str[first] == '\"')
		first++;
	while (word->str[--size] == '\"')
		lasts++;
	if (first != lasts && !g_shell.had_bslash)
	{
		g_shell.error = true;
		ft_putstr_fd(STDERR_FILENO, "Syntax errorasd\n");
		ft_lstclear(&g_shell.tokens);
		g_shell.last_return = 2;
		return (NULL);
	}
	if (g_shell.had_bslash)
		first--;
	word->str = ft_substr(word->str, first, size + 1 - lasts);
	if (DEBUG)
		printf("substr [%s]\n", word->str);
	word->str = parse_tokens(word);
	return (word->str);
}

char	*parse_d_quotes(t_ptoken *word)
{
	word->str = count_and_trim(word, ft_strlen(word->str));
	return (word->str);
}
