#include "../includes/minishell.h"

int	builtin_unset(char **argv)
{
	if (!argv[1])
		return (0);
	set_env(argv[1], NULL);
	return (0);
}
