#include "../includes/minishell.h"

void	ft_putcolor(char *str, char *color)
{
	ft_putstr(color);
	ft_putstr(str);
	ft_putstr(_END);
}
