#include "../includes/minishell.h"

char	*treat_dollar(char *word, int i, int env)
{
	char	*buff;
	char	*env_value;
	char	*new_word;

	buff = ft_strndup(word, i);
	printf("buff = [%s]\n", buff);
	env_value = get_env(word + i + env);
	printf("env = [%s]\n", env_value);
	new_word = ft_strjoin(buff, env_value);
	printf("new = [%s]\n", new_word);
	new_word = ft_strjoin(new_word, word + ft_strlen(buff) + ft_strlen(env_value));
	return (new_word);
}

void	treat_several_dollars(char *word)
{
	char	**array;
	int		j;

	j = 0;
	array = ft_split(word, '$');
	while (array[j])
	{
		printf("before array [%s]\n", array[j]);
		treat_dollar(array[j], 0, 0);
		printf("array [%s]\n", array[j]);
		j++;
	}
}


char	*parse_env_var(char *word)
{
	int	i;
	char	*new;

	i = 0;
	new = word;
	if (check_occurence(word, '$') > 1)
		treat_several_dollars(word);
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