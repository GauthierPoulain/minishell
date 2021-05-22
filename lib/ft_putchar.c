#include "../includes/minishell.h"

int	ft_putchar_fd(int fd, int c)
{
	return (write(fd, &c, 1));
}

int	ft_putchar(int c)
{
	return (ft_putchar_fd(1, c));
}
