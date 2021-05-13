#include "../includes/minishell.h"

static int	ft_atoi_calcsign(int pos, int neg)
{
	if ((!pos && !neg) || (pos == 1 && !neg))
		return (1);
	else if (!pos && neg == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	char		*tstr;
	int			pos;
	int			neg;
	int			res;

	if (!str)
		return (0);
	tstr = (char *)str;
	res = 0;
	pos = 0;
	neg = 0;
	while (ft_isspace(*tstr))
		tstr++;
	while (*tstr == '+' || *tstr == '-')
	{
		if (*tstr++ == '+')
			pos++;
		else
			neg++;
	}
	while (ft_isdigit(*tstr))
		res = (res * 10) + (*tstr++ - '0');
	return (res * ft_atoi_calcsign(pos, neg));
}

size_t	ft_atoi_len(const char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}
