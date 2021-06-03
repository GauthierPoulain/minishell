#include "../../includes/minishell.h"

int	commant_not_found(char *cmd)
{
	ft_putstr_fd(STDERR_FILENO, "minishell: command not found: ");
	ft_putstr_fd(STDERR_FILENO, cmd);
	ft_putstr_fd(STDERR_FILENO, "\n");
	return (127);
}

int	file_not_found(char *file)
{
	ft_putstr_fd(STDERR_FILENO, "minishell: file not found: ");
	ft_putstr_fd(STDERR_FILENO, file);
	ft_putstr_fd(STDERR_FILENO, "\n");
	return (1);
}

int	syntax_error(void)
{
	ft_putstr_fd(STDERR_FILENO, "minishell: syntax error\n");
	return (126);
}
