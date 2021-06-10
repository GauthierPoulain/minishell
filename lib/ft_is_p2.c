#include "../includes/minishell.h"

bool	ft_isspace(char c)
{
	printf("chqrrr %d %c\n", c, c);
	return ((c >= 9 && c <= 13) || c == ' ');
}

bool	ft_ischarset(char c, char *charset)
{
	int		i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

bool	ft_isinrange(long long value, long long min, long long max)
{
	return (value >= min && value <= max);
}
