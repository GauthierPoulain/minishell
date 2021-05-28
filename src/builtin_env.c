#include "../includes/minishell.h"

int	builtin_env(bool print_export)
{
	t_list	*actual;
	t_env	*content;

	actual = g_shell.env;
	while (actual)
	{
		content = actual->content;
		if (content && (print_export || content->value))
		{
			if (print_export)
				ft_putstr("export ");
			ft_putstr(content->key);
			if (content->value)
			{
				ft_putstr("=");
				ft_putstr(content->value);
			}
			ft_putstr("\n");
		}
		actual = actual->next;
	}
	return (0);
}
