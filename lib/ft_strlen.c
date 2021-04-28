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

static int	is_utf8_character(unsigned char c)
{
	if ((c >> 7) == 1)
	{
		if ((c >> 6) == 2)
			return (2);
		else
			return (1);
	}
	return (0);
}

size_t	ft_realstren(char *str)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_utf8_character(str[i]) == 0)
			count += 1;
		else if (is_utf8_character(str[i]) == 1)
			count += 2;
	}
	return (count);
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