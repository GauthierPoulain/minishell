#include "../includes/minishell.h"

void	print_err(char *msg)
{
	ft_putstr_fd(STDERR_FILENO, "exit: ");
	ft_putstr_fd(STDERR_FILENO, msg);
	ft_putstr_fd(STDERR_FILENO, "\n");
	close_shell(1);
}

int	close_shell(int code)
{
	gc_clean();
	close(g_shell.saved_stdout);
	close(g_shell.saved_stderr);
	if (isatty(STDIN_FILENO))
		reset_input_mode();
	exit(code);
	return (0);
}

void	close_subprocess(int code)
{
	gc_clean();
	exit(code);
}
