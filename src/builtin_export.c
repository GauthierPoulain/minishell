#include "../includes/minishell.h"

int	builtin_export(char **argv)
{
	if (!argv[1])
		builtin_env();
	else
	{
		if (!argv[2])
		{
			if (!get_env(argv[1]))
				set_env(argv[1], "''");
		}
		else
			set_env(argv[1], argv[2]);
	}
	return (0);
}
