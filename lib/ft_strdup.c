#include "../includes/minishell.h"

char	*ft_strdup(char *s1)
{
	char	*str;
	int		len;
	int		i;

	len = ft_strlen(s1);
	str = gc_malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
