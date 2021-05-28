#include "../includes/minishell.h"

int	builtin_export(char **argv)
{
	char	**export;

	if (!argv[1])
		builtin_env();
	else
	{
		export = ft_split(argv[1], '=');
		if (!export[1])
		{
			if (!get_env(export[0]))
				set_env(export[0], "''");
		}
		else
			set_env(export[0], export[1]);
	}
	return (0);
}
