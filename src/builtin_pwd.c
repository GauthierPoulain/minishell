#include "../includes/minishell.h"

int	builtin_pwd(void)
{
	ft_putstr(get_env("PWD"));
	ft_putstr("\n");
	return (0);
}
