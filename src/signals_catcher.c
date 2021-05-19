#include "../includes/minishell.h"

void	SIGINT_catcher(int code)
{
	(void)code;
	signal(SIGINT, SIGINT_catcher);
	g_shell.actual_str = ft_calloc(sizeof(char *));
	ft_putchar('\n');
	g_shell.last_return = 130;
	pre_prompt();
}

void	SIGQUIT_catcher(int code)
{
	(void)code;
}

void	SIGQUIT_catcher_subprocess(int code)
{
	(void)code;
	printf("lolz\n");
	gc_clean();
	g_shell.last_return = 131;
	exit(131);
}

void	redir_sig_to_child(int code)
{
	kill(g_shell.child, code);
}

void	signals_listeners_to_child(void)
{
	signal(SIGINT, redir_sig_to_child);
	signal(SIGQUIT, redir_sig_to_child);
}

void	reset_signals_listeners(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	add_signals_listeners(void)
{
	signal(SIGINT, SIGINT_catcher);
	signal(SIGQUIT, SIGQUIT_catcher);
}
