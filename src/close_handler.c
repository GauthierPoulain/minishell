#include "../includes/minishell.h"

void	print_err(char *msg)
{
	ft_putstr_fd(2, "exit: ");
	ft_putstr_fd(2, msg);
	ft_putstr_fd(2, "\n");
}

void	close_shell(char *msg)
{
	gc_clean();
	if (msg)
	{
		if (DEBUG)
			print_err(msg);
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);
}
