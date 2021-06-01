#include "../../includes/minishell.h"

void	fetch_pipe_output(void)
{
	g_shell.need_pipe = false;
}

void	close_pipe(void)
{
	if (g_shell.outputmngr)
	{
		close(g_shell.pipes.to_son[0]);
		close(g_shell.pipes.to_son[1]);
		close(g_shell.pipes.to_father[1]);
		close(g_shell.pipes.to_father[0]);
		if (g_shell.need_pipe)
			fetch_pipe_output();
		reset_output();
		waitpid(g_shell.outputmngr, NULL, 0);
	}
	g_shell.outputmngr = 0;
}
