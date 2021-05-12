#include "../includes/minishell.h"

static char	*treat_non_dollar(char *word, int *no_dollar)
{
	int		len;
	char	*new_word;
	char	*env_value;

	*no_dollar = 0;
	len = ft_strlen_charset(word, "$");
	new_word = ft_strndup(word, len);
	env_value = get_env(word + len);
	new_word = ft_strjoin(new_word, env_value);
	return (new_word);
}

char	*treat_dollar(char *word, int *no_dollar)
{
	char	*env_value;
	char	*new_word;

	if (DEBUG)
		printf("word during treat [%s]\n", word);
	if (*no_dollar)
		return (treat_non_dollar(word, no_dollar));
	else if (word[0] == '/')
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
	// int		i;
	// char	*new;

	// i = 0;
	// new = word;
	// if (DEBUG)
	// 	printf("word [%s]\n", word);
	// if (check_occurence(word, '$') > 1)
	// 	return (treat_several_dollars(word));
	// else
	// {
	// 	while (new[i])
	// 	{
	// 		if (new[i] == '$')
	// 			new = treat_several_dollars(word);
	// 		i++;
	// 	}
	// }
	// return (new);
}
