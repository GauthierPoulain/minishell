#include "../../includes/minishell.h"

int	commant_not_found(char *cmd)
{
	ft_putstr_fd(2, "minishell: command not found: ");
	ft_putstr_fd(2, cmd);
	ft_putstr_fd(2, "\n");
	return (127);
}

int	syntax_error(void)
{
	ft_putstr_fd(2, "minishell: syntax error\n");
	return (126);
}
