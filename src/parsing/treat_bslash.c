#include "../../includes/minishell.h"

char	*bslash_nquotes(t_ptoken *word, int *i, int r_back)
{
	int		f_quotes;
	int		l_quotes;
	int		size;
	char	*new;

	f_quotes = 0;
	l_quotes = 0;
	while (word->str[*i] == '\"')
	{
		*i += 1;
		f_quotes++;
	}
	size = ft_strlen(word->str + *i);
	while (word->str[size] == '\"')
	{
		l_quotes++;
		size--;
	}
	new = ft_substr(word->str, f_quotes + r_back,
			ft_strlen(word->str + *i) + 1 - l_quotes);
	new = parse_d_quotes(word);
	return (new);
}

char	*bslash_filled(t_ptoken *word, int back)
{
	char	*new;
	int		r_back;

	(void)word;
	r_back = back / 2;
	r_back++;
	new = ft_calloc_char(r_back, '\\');
	if (back % 4 == 1 || back % 4 == 3)
		g_shell.trans = 1;
	else
		g_shell.trans = 0;
	printf("NEW [%s]\n", new);
	return (new);
}

char	*error_bslash(void)
{
	ft_putstr_fd(STDERR_FILENO, "Syntax error BSLASH\n");
	ft_lstclear(&g_shell.tokens);
	g_shell.last_return = 2;
	g_shell.error = true;
	return (NULL);
}
