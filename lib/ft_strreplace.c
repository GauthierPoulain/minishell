#include "../includes/minishell.h"

char	*ft_strreplace(char *str, char *substr, char *replace)
{
	char	*res;
	char	*location;
	int		i;

	location = ft_strstr(str, substr);
	if (!location)
		return (str);
	res = ft_calloc(sizeof(char) * (ft_strlen(str) - ft_strlen(substr)
				+ ft_strlen(replace) + 1));
	i = 0;
	while (str + i != location)
	{
		res[i] = str[i];
		i++;
	}
	ft_strcat(res, replace);
	while (str[i + ft_strlen(substr)])
	{
		res[i + ft_strlen(replace)] = str[i + ft_strlen(substr)];
		i++;
	}
	return (res);
}
