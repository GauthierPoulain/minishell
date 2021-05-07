#include "../includes/minishell.h"

char	*treat_dollar(char *word)
{
	// char	*buff;
	char	*env_value;
	char	*new_word;

	if (DEBUG)
		printf("word during treat [%s]\n", word);
	if (word[0] == '/')
	{
		new_word = ft_strdup("$");
		new_word = ft_strjoinf2(new_word, word);
		return (new_word);
	}
	env_value = get_env(word);
	new_word = ft_strdup(env_value);
	return (new_word);
}

char	*join_tab(char **array)
{
	int		i;
	char	*res;

	i = 1;
	res = ft_strdup(array[0]);
	while (array[i])
		res = ft_strjoin(res, array[i++]);
	if (DEBUG)
		printf("res [%s]\n", res);
	return (res);
}

char	*treat_several_dollars(char *word)
{
	char	**array;
	int		j;
	int		has_dollar;

	has_dollar = 0;
	if (word[0] != '$')
		has_dollar = 1;
	j = 0;
	array = ft_split(word, '$');
	while (array[j])
	{
		if (DEBUG)
			printf("array[%s] (before)\n", array[j]);
		array[j] = treat_dollar(array[j]);
		if (DEBUG)
			printf("array[%s] (after)\n", array[j]);
		j++;
	}
	return (join_tab(array));
}

char	*parse_env_var(char *word)
{
	int		i;
	char	*new;

	i = 0;
	new = word;
	printf("word [%s]\n", word);
	if (check_occurence(word, '$') > 1)
		return (treat_several_dollars(word));
	else
	{
		while (new[i])
		{
			if (new[i] == '$')
				new = treat_several_dollars(word);
			i++;
		}
	}
	return (new);
}
