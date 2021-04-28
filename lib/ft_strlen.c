#include "../includes/minishell.h"

size_t	ft_strlen(char *str)
{
	char	*s;

	if (!str)
		return (0);
	s = str;
	while (*str)
		++str;
	return (str - s);
}

size_t	ft_strlen_charset(char *str, char *charset)
{
	char	*s;

	if (!str)
		return (0);
	s = str;
	while (*str && !ft_ischarset(*str, charset))
		++str;
	return (str - s);
}
