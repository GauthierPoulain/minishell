#include "../includes/minishell.h"

char	*treat_several_dollars(char *word)
{
	char	**array;
	int		j;
	int		no_dollar;

	no_dollar = 0;
	if (word[0] != '$')
		no_dollar = 1;
	j = 0;
	array = ft_split(word, '$');
	while (array[j])
	{
		if (DEBUG)
			printf("array[%s] (before)\n", array[j]);
		array[j] = treat_dollar(array[j], &no_dollar);
		if (DEBUG)
			printf("array[%s] (after)\n", array[j]);
		j++;
	}
	return (join_tab(array));
}

int		check_slash(char *word, int i)
{
	int	j;

	j = i;
	while (word[i])
	{
		if (word[i] == '$')
			return (0);
		else if (word[i] == '/')
			return (i - j);
		i++;
	}
	return (0);
}

char	*treat_doll(char *word, int i)
{
	int		back;
	char	*ret;
	char	*env_value;

	if (DEBUG)
		printf("word [%s]\n", word);
	back = check_slash(word, i + 1);
	if (back)
	{
		env_value = get_env(ft_strndup(word + i + 1, back));
		back++;
		if (env_value)
		{
			ret = ft_strndup(word, i);
			ret = ft_strjoin(ret, env_value);
			ret = ft_strjoin(ret, word + i + back);
		}
		else
		{
			ret = ft_strndup(word, i);
			ret = ft_strjoin(ret, word + i + back);
			// printf("ret : [%s]\n", ret);
		}
		return (ret);
	}
	return (word);
}

char	*parse_test(char *word)
{
	int		i;
	char	*new;

	i = 0;
	new = word;
	while (new[i])
	{
		if (new[i] == '$')
			new = treat_doll(new, i);
		i++;
	}
	return (new);
}

char	*parse_env_var(char *word)
{
	return (parse_test(word));
}
