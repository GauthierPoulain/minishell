#include "../includes/minishell.h"

int	builtin_export(char **argv)
{
	char	**export;
	int		i;
	int		ret;

	ret = 0;
	if (!argv[1])
		builtin_env(true);
	else
	{
		i = 1;
		while (argv[i])
		{
			if (!ft_strchr(argv[i], '='))
			{
				ft_putstr_fd(STDERR_FILENO, "minishell: invalid export param\n");
				ret = 1;
			}	
			else
			{
				export = ft_split(argv[i], '=');
				if (!export[1])
				{
					if (!get_env(export[0]))
						set_env(export[0], NULL);
				}
				else
				set_env(export[0], export[1]);
			}
			i++;
		}
	}
	return (ret);
}
