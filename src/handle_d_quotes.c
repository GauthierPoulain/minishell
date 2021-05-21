#include "../includes/minishell.h"

static char	*trim_d_quotes(char *word, int first, int lasts, size_t size)
{
	return (ft_substr(word, first, size - lasts));
}

static int	count_d_quotes(char *word, size_t size)
{
	int	first;
	int	lasts;
	int	diff;

	first = 0;
	lasts = 0;
	while (word[first] == '\\')
		first++;
	while (word[--size] == '\\')
		lasts++;
	diff = first - lasts;
	if (diff < 0)
		diff = !diff;
	word = trim_d_quotes(word, first, lasts, size);
	return (diff);
}


char	*parse_d_quotes(char *word)
{
	if (count_d_quotes(word, ft_strlen(word)) % 2)
	{
		ft_putstr_fd(2, "Syntax error");
		return ("");
	}
	return (word);
}