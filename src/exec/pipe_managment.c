#include "../../includes/minishell.h"

void	fetch_pipe_output(void)
{
	g_shell.pipe_output.ptr = ft_calloc(12);
	read(g_shell.pipes.to_father[0], g_shell.pipe_output.ptr, 8);
	g_shell.pipe_output.size = *g_shell.pipe_output.ptr;
	g_shell.pipe_output.ptr = ft_calloc(sizeof(char)
			* (g_shell.pipe_output.size + 1));
	read(g_shell.pipes.to_father[0], g_shell.pipe_output.ptr,
		g_shell.pipe_output.size);
	g_shell.need_pipe = false;
}

void	close_pipe(void)
{
	if (g_shell.outputmngr)
	{
		close(g_shell.pipes.to_son[1]);
		close(g_shell.pipes.to_father[1]);
		reset_output();
		fetch_pipe_output();
		waitpid(g_shell.outputmngr, NULL, 0);
		g_shell.outputmngr = 0;
	}
}
