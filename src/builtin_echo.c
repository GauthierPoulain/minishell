#include "../includes/minishell.h"

int	builtin_echo(char **str)
{
	int		i;

	if (str[0] && str[1] && !ft_strcmp(str[1], "-e"))
	{
		i = 2;
		while (str[i])
			ft_putstr(str[i++]);
	}
	else
	{
		i = 1;
		while (str[i])
			ft_putstr(str[i++]);
		ft_putstr("\n");
	}
	return (0);
}
