#include "../includes/minishell.h"

int	builtin_exit(char **argv)
{
	int		ret;

	ret = 0;
	if (argv[1])
		ret = ft_atoi(argv[1]);
	gc_clean();
	exit(ret);
}
