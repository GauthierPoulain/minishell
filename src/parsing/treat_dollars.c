#include "../../includes/minishell.h"

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
	if ((word + (*i + 1))->escapes > 0)
	{
		*i += get_word_len(word->str, *i) + 2;
		return (ft_strjoin("$", word->str));
	}
	else if (word->str[(*i) + 1] == '/')
	{
		printf("salut %d\n", *i);
		*i += get_word_len(word->str, *i) + 1;
		return (word->str);
	}
	else
		return (replace_dolls(word, i));
}
