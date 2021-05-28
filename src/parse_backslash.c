#include "../includes/minishell.h"

static size_t	bslash_f_count(char *word, int i)
{
	int	j;

	j = 0;
	while (word[i] == '\\')
	{
		i++;
		j++;
	}
	return (j);
}

char	*special_trim_quotes(char *word)
{
	int		first;
	int		lasts;
	int		size;
	char	*new;

	first = 0;
	lasts = 0;
	size = ft_strlen(word);
	while (word[first] == '\"')
		first++;
	while (word[--size] == '\"')
		lasts++;
	new = ft_substr(word, first, size + 2 - lasts);
	return (new);
}

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
		printf("SALUT\n");
		*i += 1;
		f_quotes++;
	}
	size = ft_strlen(word + *i);
	while (word[size] == '\"')
	{
		l_quotes++;
		size--;
	}
	new = ft_substr(word, f_quotes + r_back, ft_strlen(word + *i) + 1 - l_quotes);
	new = parse_d_quotes(new);
	printf("after the magical sub : [%s]\n", new);
	return (new);
}

char	*bslash_filled(char *word, int *i, int *trans, int back)
{
	char	*new;
	int		r_back;

	r_back = back / 2;
	new = ft_calloc_char(r_back + 1, '\\');
	new = ft_strjoin(new, word + back + *i);
	*i += r_back;
	if (back % 4 == 1 || back % 4 == 3)
		*trans = 1;
	else
		*trans = 0;
	while (word[*i] == '\\')
		*i += 1;
	if (word[*i] == '\"')
		new = bslash_nquotes(word, i, r_back);
	new = parse_tokens(new);
	printf("NEW [%s]\n", new);
	return (new);
}

static char	*error_bslash(int *i)
{
	*i = 0;
	printf("JE SUIS LA EN FAIT\n");
	ft_putstr_fd(2, "Syntax error\n");
	ft_lstclear(&g_shell.tokens);
	g_shell.last_return = 1;
	g_shell.error = true;
	return ("");
}

char	*treat_backslash(char *word, int *i, int *trans)
{
	int		back;

	back = bslash_f_count(word, *i);
	printf("string [%s] and i value : %d\n", word, *i);
	printf("back : %d and strlen (%zu)\n *i is %d\n", back, ft_strlen(word), *i);
	if (back % 2 && ft_strlen(word) == *i + (size_t)back)
		return (error_bslash(i));
	if (*i == 0)
		return (bslash_filled(word, i, trans, back));
	else
		return (ft_strjoin(ft_strndup(word, *i),
				bslash_filled(word, i, trans, back)));
}
