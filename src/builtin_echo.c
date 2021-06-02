#include "../includes/minishell.h"

static bool	skip_n(char **argv, int *i)
{
	bool	ret;

	ret = false;
	while (argv[*i] && !ft_strcmp(argv[*i], "-n"))
	{
		ret = true;
		*i += 1;
	}
	return (ret);
}

int	builtin_echo(char **str)
{
	int		i;

	i = 1;
	if (str[0] && skip_n(str, &i))
	{
		while (str[i])
		{
			ft_putstr(str[i++]);
			if (str[i])
				ft_putstr(" ");
		}
	}
	else
	{
		while (str[i])
		{
			ft_putstr(str[i++]);
			if (str[i])
				ft_putstr(" ");
		}
		ft_putstr("\n");
	}
	return (0);
}
