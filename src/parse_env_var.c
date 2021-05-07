#include "../includes/minishell.h"

char	*treat_several_dollars(char *word, int i)
{
	
}

char	*treat_dollar(char *word, int i)
{
	char	*buff;
	char	*env_value;
	char	*new_word;

	if (check_occurence(word + i, '$') > 1)
		return (treat_several_dollars(word, i));
	buff = ft_strndup(word, i);
	printf("buff = [%s]\n", buff);
	env_value = get_env(word + i + 1);
	printf("env = [%s]\n", env_value);
	new_word = ft_strjoin(buff, env_value);
	printf("new = [%s]\n", new_word);
	new_word = ft_strjoin(new_word, word + ft_strlen(buff) + ft_strlen(env_value));
	return (new_word);
}

char	*parse_env_var(char *word)
{
	int	i;
	char	*new;

	i = 0;
	new = word;
	while (new[i])
	{
		if (new[i] == '$' && new[i + 1] != '\\')
			new = treat_dollar(new, i);
		i++;
	}
	return (new);
}