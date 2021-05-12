#include "../includes/minishell.h"

char	*treat_doll_backslash(char *word, int i, int back)
{
	char	*env_value;
	char	*ret;

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

static size_t	get_word_len(char *word, int i)
{
	int	j;

	j = 0;
	while (word[i])
	{
		if (word[i] == ' ' || word[i] == '$')
			return (j);
		i++;
		j++;
	}
	return (j);
}

char	*replace_dolls(char *word, int i)
{
	char	*ret;
	char	*env_value;
	int		len;

	ret = ft_strndup(word, i);
	printf("ret no slash : [%s]\n", ret);
	len = get_word_len(word, ft_strlen(ret) + 1);
	printf("len [%d]\n", len);
	printf("yes [%s]\n", ft_strndup(word + i + 1, len));
	env_value = get_env(ft_strndup(word + i + 1, len));
	printf("env value : [%s]\n", env_value);
	ret = ft_strjoin(ret, env_value);
	ret = ft_strjoin(ret, word + i + len + 1);
	printf("ret before last : [%s]\n", ret);
	return (ret);
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

	if (DEBUG)
		printf("word [%s]\n", word);
	if (word[i + 1] == '/')
		return (word);
	back = check_slash(word, i + 1);
	if (back)
		return (treat_doll_backslash(word, i, back));
	else
		return (replace_dolls(word, i));
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
	printf("retun new : [%s]\n", new);
	return (new);
}

char	*parse_env_var(char *word)
{
	return (parse_test(word));
}
