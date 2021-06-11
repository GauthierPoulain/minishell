#include "../includes/minishell.h"

static void	run_export(char *argv)
{
	char	**export;

	export = ft_split(argv, '=');
	if (!export[1])
		set_env(export[0], NULL);
	else
		set_env(export[0], ft_strtrim_spaces(export[1]));
}

int	builtin_export(char **argv)
{
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
				run_export(argv[i]);
			i++;
		}
	}
	return (ret);
}
