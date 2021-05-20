#include "../includes/minishell.h"

int	builtin_exit(char **argv)
{
	gc_clean();
	exit(ft_atoi(argv[1]));
}
