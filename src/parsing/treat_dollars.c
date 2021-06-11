#include "../../includes/minishell.h"

char	*treat_doll_slash(char *word, int *i, int back)
{
	char	*env_value;
	char	*ret;

	env_value = get_env(ft_strndup(word + (*i) + 1, back));
	back++;
	if (env_value)
	{
		ret = ft_strndup(word, *i);
		ret = ft_strjoin(ret, env_value);
		ret = ft_strjoin(ret, word + (*i) + back);
	}
	else
	{
		ret = ft_strndup(word, *i);
		ret = ft_strjoin(ret, word + (*i) + back);
	}
	return (ret);
}

char	*replace_dolls(t_ptoken *word, int *i)
{
	char	*ret;
	char	*env_value;
	int		len;

	ret = ft_strndup(word->str, *i);
	len = get_word_len(word->str, ft_strlen(ret) + 1);
	if (word->str[*i + 1] == '?')
		env_value = ft_itoa(g_shell.last_return);
	else
		env_value = get_env(ft_strndup(word->str + *i + 1, len));
	ret = ft_strjoin(ret, env_value);
	ret = ft_strjoin(ret, word->str + (*i) + len + 1);
	word->str = ret;
	if (len > (int)ft_strlen(env_value))
		*i += len;
	else
		*i += ft_strlen(env_value);
	return (ret);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int			i;
	char		*bdst;
	const char	*bsrc;

	if (!dst && !src)
		return (NULL);
	i = 0;
	bsrc = src;
	bdst = dst;
	if (src > dst)
	{
		while ((unsigned long)i < len)
		{
			bdst[i] = bsrc[i];
			i++;
		}
	}
	else
		while (len--)
			bdst[len] = bsrc[len];
	return (dst);
}

char	*treat_doll(t_ptoken *word, int *i)
{
	int		slash;

	if (word->str[(*i) + 1] == '\\')
	{
		word->str = ft_strjoin(ft_strndup(word->str, (*i) + 1),
				word->str + (*i) + 2);
		*i += 1;
		*i += get_word_len(word->str, *i);
		return (word->str);
	}
	else if (word->str[(*i) + 1] == '/')
	{
		*i += 1;
		*i += get_word_len(word->str, *i);
		return (word->str);
	}
	else
	{
		slash = check_slash(word, (*i) + 1);
		if (slash)
			return (treat_doll_slash(word->str, i, slash));
		else
			return (replace_dolls(word, i));
	}
	return (word->str);
}
