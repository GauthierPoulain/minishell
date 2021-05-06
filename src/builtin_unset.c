#include "../includes/minishell.h"

int	builtin_unset(char **argv)
{
	if (!argv[1])
	{
		ft_putstr_fd(2, "unset: not enough arguments\n");
		return (1);
	}
	set_env(argv[1], NULL);
	return (0);
}
