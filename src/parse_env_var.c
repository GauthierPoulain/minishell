#include "../includes/minishell.h"

char	*treat_dollar(char *word, int i, int env)
{
	char	*buff;
	char	*env_value;
	char	*new_word;

	buff = ft_strndup(word, i);
	env_value = get_env(word + i + env);
	new_word = ft_strjoin(buff, env_value);
	if (ft_strlen(buff))
		new_word = ft_strjoin(new_word,
				word + ft_strlen(buff) + ft_strlen(env_value));
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

	j = 0;
	array = ft_split(word, '$');
	while (array[j])
	{
		array[j] = treat_dollar(array[j], 0, 0);
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
	if (check_occurence(word, '$') > 1)
		return (treat_several_dollars(word));
	else
	{
		while (new[i])
		{
			if (new[i] == '$' && new[i + 1] != '\\')
				new = treat_dollar(new, i, 1);
			i++;
		}
	}
	return (new);
}
