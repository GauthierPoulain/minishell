#include "../includes/minishell.h"

int	builtin_exit(char **argv)
{
	int		ret;

	ret = 0;
	if (isatty(STDIN_FILENO))
		ft_putstr("exit\n");
	if (argv && argv[1])
		ret = ft_atoi(argv[1]);
	close_pipe();
	gc_clean();
	exit(ret);
}
