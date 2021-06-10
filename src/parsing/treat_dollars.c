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

char	*replace_dolls(t_ptoken *word, int i)
{
	char	*ret;
	char	*env_value;
	int		len;

	ret = ft_strndup(word->str, i);
	len = get_word_len(word->str, ft_strlen(ret) + 1);
	if (word->str[i + 1] == '?')
		env_value = ft_itoa(g_shell.last_return);
	else
		env_value = get_env(ft_strndup(word->str + i + 1, len));
	ret = ft_strjoin(ret, env_value);
	ret = ft_strjoin(ret, word->str + i + len + 1);
	printf("ret = %s\n", ret);
	word->str = ret;
	return (ret);
}

char	*treat_doll(t_ptoken *word, int *i)
{
	int		slash;

	// if (DEBUG)
	// 	printf("trans: %d\nis in quotes: %d\nhas space: %d\n",
	// 		g_shell.trans, g_shell.is_in_s_quotes, g_shell.curr_token->sp);
	// if ((g_shell.trans == 1 && !g_shell.curr_token->sp)
	// 	|| (g_shell.is_in_s_quotes && !g_shell.curr_token->sp))
	// {
	// 	g_shell.trans = 0;
	// 	*i += 1;
	// 	return (word->str);
	// }
	if (DEBUG)
		printf("word [%s]\n", word->str);
	if (word->str[(*i) + 1] == '/')
		return (word->str);
	slash = check_slash(word, (*i) + 1);
	if (slash)
		return (treat_doll_slash(word->str, (*i), slash));
	else
		return (replace_dolls(word, (*i)));
	// return (word->str);
}
