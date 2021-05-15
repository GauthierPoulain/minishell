#include "../includes/minishell.h"

int	ft_putchar(int c)
{
	return (write(g_shell.io.cout, &c, 1));
}
