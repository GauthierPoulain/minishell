#include "../includes/minishell.h"

char	*ft_strtrim_spaces(char *str)
{
	char	*res;
	size_t	len;

	while (ft_isspace(*str))
		str++;
	len = ft_strlen(str);
	if (len > 0)
	{
		while (ft_isspace(str[len - 1]))
		{
			printf("len = %zu\n", len);
			len--;
		}
	}
	res = ft_strndup(str, len);
	return (res);
}
