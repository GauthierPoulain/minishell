#include "../includes/minishell.h"

void	print_err(char *msg)
{
	ft_putstr_fd(STDERR_FILENO, "exit: ");
	ft_putstr_fd(STDERR_FILENO, msg);
	ft_putstr_fd(STDERR_FILENO, "\n");
}

int	close_shell(char *msg)
{
	gc_clean();
	close(g_shell.saved_stdout);
	close(g_shell.saved_stderr);
	if (isatty(STDIN_FILENO))
		reset_input_mode();
	if (msg)
	{
		if (DEBUG)
			print_err(msg);
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);
	return (0);
}

void	close_subprocess(int code)
{
	gc_clean();
	exit(code);
}
