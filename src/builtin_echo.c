#include "../includes/minishell.h"

static bool	skip_n(char **argv, int *i)
{
	bool	ret;
	char	*save;

	ret = false;
	while (argv[*i] && argv[*i][0] == '-')
	{
		save = argv[*i] + 1;
		while (save && *save == 'n')
			save++;
		if (*save == 0)
		{
			*i += 1;
			ret = true;
		}
		else
			return (ret);
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
				ft_putstr("\n");
		}
		ft_putstr("\n");
	}
	return (0);
}
