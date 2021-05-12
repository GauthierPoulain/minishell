#include "../includes/minishell.h"

static void	ctrlc_catcher(int code)
{
	(void)code;
	g_shell.actual_str = ft_calloc(sizeof(char *));
	ft_putchar('\n');
	pre_prompt();
}

void	add_signals_listeners(void)
{
	signal(SIGINT, ctrlc_catcher);
}
