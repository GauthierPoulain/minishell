#include "../includes/minishell.h"

static int	count_words(char const *s)
{
	int		i;
	int		words;
	int		check;

	i = 0;
	words = 0;
	while (s[i])
	{
		check = 0;
		while (ft_isspace(s[i]) && s[i])
			i++;
		while (!ft_isspace(s[i]) && s[i])
		{
			i++;
			check = 1;
		}
		words += check;
	}
	return (words);
}

static int	get_word_length(char const *s, int i)
{
	int		l;

	l = 0;
	while (s[i] && !ft_isspace(s[i]))
	{
		i++;
		l++;
	}
	return (l);
}

char	**ft_split_spaces(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	**res;

	if (!s)
		return (NULL);
	res = gc_malloc(sizeof(char *) * (count_words(s) + 1));
	i = 0;
	k = 0;
	while (k < count_words(s))
	{
		j = 0;
		while (ft_isspace(s[i]))
			i++;
		res[k] = gc_malloc(sizeof(char) * (get_word_length(s, i) + 1));
		while (s[i] && !ft_isspace(s[i]))
			res[k][j++] = s[i++];
		res[k][j] = 0;
		k++;
	}
	res[k] = NULL;
	return (res);
}
