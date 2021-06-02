#include "../../includes/minishell.h"

char	*bslash_nquotes(char *word, int *i, int r_back)
{
	int		f_quotes;
	int		l_quotes;
	int		size;
	char	*new;

	f_quotes = 0;
	l_quotes = 0;
	while (word[*i] == '\"')
	{
		*i += 1;
		f_quotes++;
	}
	size = ft_strlen(word + *i);
	while (word[size] == '\"')
	{
		l_quotes++;
		size--;
	}
	new = ft_substr(word, f_quotes + r_back - 1,
			ft_strlen(word + *i) + 1 - l_quotes);
	printf("substr part [%s]\n", new);
	g_shell.had_bslash = true;
	new = parse_d_quotes(new);
	g_shell.had_bslash = false;
	printf("after parse inside slash : [%s]\n", new);
	return (new);
}

char	*bslash_filled(char *word, int *i, int *trans, int back)
{
	char	*new;
	int		r_back;
	int		tmp;

	r_back = back / 2;
	if (g_shell.is_in_quotes == false)
		r_back++;
	tmp = *i;
	new = ft_calloc_char(r_back, '\\');
	new = ft_strjoin(new, word + back + *i);
	*i += r_back;
	if (back % 4 == 1 || back % 4 == 3)
		*trans = 1;
	else
		*trans = 0;
	if (*i == (int)ft_strlen(word))
		*i = tmp;
	printf("word i [%c]\n", word[*i]);
	if (back > 1)
		*i += 1;
	printf("word i [%c]\n", word[*i]);
	if (word[*i] == '\"')
	{
		new = bslash_nquotes(word, i, r_back);
		if (*i >= (int)ft_strlen(word))
			*i = (int)ft_strlen(word);
	}
	g_shell.is_in_quotes = false;
	return (new);
}

char	*error_bslash(int *i)
{
	*i = 0;
	ft_putstr_fd(2, "Syntax error\n");
	ft_lstclear(&g_shell.tokens);
	g_shell.last_return = 1;
	g_shell.error = true;
	return ("");
}
