#include "../includes/minishell.h"

void	SIGINT_catcher(int code)
{
	(void)code;
	signal(SIGINT, SIGINT_catcher);
	g_shell.actual_str = ft_calloc(sizeof(char *));
	ft_putchar('\n');
	g_shell.last_return = 130;
	g_shell.history.act_pos = 0;
	pre_prompt();
}

void	signal_nothing(int code)
{
	(void)code;
}

void	redir_sig_to_child(int code)
{
	if (code == SIGINT)
		g_shell.last_return = 130;
	else if (code == SIGQUIT)
		g_shell.last_return = 131;
	kill(g_shell.child, code);
	g_shell.child = 0;
	if (g_shell.outputmngr)
		kill(g_shell.outputmngr, code);
	g_shell.outputmngr = 0;
}

void	signals_listeners_to_child(void)
{
	signal(SIGINT, redir_sig_to_child);
	signal(SIGQUIT, redir_sig_to_child);
}

void	add_signals_listeners(void)
{
	signal(SIGINT, SIGINT_catcher);
	signal(SIGQUIT, signal_nothing);
}
