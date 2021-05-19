#include "../includes/minishell.h"

static void	SIGINT_catcher(int code)
{
	(void)code;
	g_shell.actual_str = ft_calloc(sizeof(char *));
	ft_putchar('\n');
	g_shell.last_return = 130;
	pre_prompt();
}

static void	SIGQUIT_catcher(int code)
{
	(void)code;

}

void	add_signals_listeners(void)
{
	signal(SIGINT, SIGINT_catcher);
	signal(SIGQUIT, SIGQUIT_catcher);
}
