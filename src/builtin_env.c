#include "../includes/minishell.h"

int	builtin_env(void)
{
	t_list	*actual;
	t_env	*content;

	actual = g_shell.env;
	while (actual)
	{
		content = actual->content;
		if (content && content->value)
		{
			ft_putstr(content->key);
			ft_putstr("=");
			ft_putstr(content->value);
			ft_putstr("\n");
		}
		actual = actual->next;
	}
	return (0);
}
