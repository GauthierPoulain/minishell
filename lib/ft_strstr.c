#include "../includes/minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = -1;
	if (!ft_strlen(to_find))
		return (str);
	while (str[++i])
	{
		j = 0;
		while (str[i + j] == to_find[j] && str[j])
		{
			j++;
			if (!to_find[j])
				return (str + i);
		}
	}
	return (NULL);
}
