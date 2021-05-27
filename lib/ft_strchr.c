#include "../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == 0)
		return ((char *)s);
	return (NULL);
}

char	*ft_memchr(const char *s, int c, int pos, size_t size)
{
	int		i;

	i = (int)size;
	while (i > pos)
	{
		if (s[i] == c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
