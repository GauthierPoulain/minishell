#include "../../includes/minishell.h"

char	*treat_doll_slash(char *word, int i, int back)
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
	}
	return (ret);
}

char	*replace_dolls(char *word, int i)
{
	char	*ret;
	char	*env_value;
	int		len;

	ret = ft_strndup(word, i);
	len = get_word_len(word, ft_strlen(ret) + 1);
	if (word[i + 1] == '?')
		env_value = ft_itoa(g_shell.last_return);
	else
		env_value = get_env(ft_strndup(word + i + 1, len));
	ret = ft_strjoin(ret, env_value);
	ret = ft_strjoin(ret, word + i + len + 1);
	return (ret);
}

char	*treat_doll(char *word, int *i, int *trans)
{
	int		slash;

	if (DEBUG)
		printf("JE SUIS UN DOLLAR\ntrans : %d, quotes = %d\n", *trans, g_shell.is_in_s_quotes);
	if (*trans == 1 || g_shell.is_in_s_quotes)
	{
		*trans = 0;
		*i += 1;
		return (word);
	}
	if (DEBUG)
		printf("word [%s]\n", word);
	if (word[(*i) + 1] == '/')
		return (word);
	slash = check_slash(word, (*i) + 1);
	if (slash)
		return (treat_doll_slash(word, (*i), slash));
	else
		return (replace_dolls(word, (*i)));
	return (word);
}
