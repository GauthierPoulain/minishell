#include "../includes/minishell.h"

static char	*trim_d_quotes(char *word, int first, int lasts, size_t size)
{
	return (ft_substr(word, first, size + 1 - lasts));
}

static char	*count_and_trim(char *word, size_t size)
{
	int	first;
	int	lasts;

	first = 0;
	lasts = 0;
	while (word[first] == '\"')
		first++;
	while (word[--size] == '\"')
		lasts++;
	printf("first : %d\nlasts : %d\n", first, lasts);
	if (first != lasts)
	{
		ft_putstr_fd(2, "Syntax error\n");
		ft_lstclear(&g_shell.tokens);
		g_shell.last_return = 1;
		return (NULL);
	}
	word = trim_d_quotes(word, first, lasts, size);
	return (word);
}


char	*parse_d_quotes(char *word)
{
	word = count_and_trim(word, ft_strlen(word));
	return (word);
}