#include "../includes/minishell.h"

void	catch_SIGINT(int sig)
{
	(void)sig;
	close_shell(NULL);
}

void	add_catchers(void)
{
	signal(SIGINT, catch_SIGINT);
}
