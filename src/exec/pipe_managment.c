#include "../../includes/minishell.h"

void	fetch_pipe_output(void)
{
	g_shell.pipe_output.ptr = ft_calloc(12);
	read(g_shell.pipes.to_father[0], g_shell.pipe_output.ptr, 8);
	g_shell.pipe_output.size = *g_shell.pipe_output.ptr;
	g_shell.pipe_output.ptr = ft_calloc(sizeof(char) * (g_shell.pipe_output.size + 1));
	read(g_shell.pipes.to_father[0], g_shell.pipe_output.ptr, g_shell.pipe_output.size);
	write(1, g_shell.pipe_output.ptr, g_shell.pipe_output.size);
	g_shell.need_pipe = false;
}

void	close_pipe(void)
{
	if (g_shell.outputmngr)
	{
		write(1, ft_calloc_char(sizeof(char) * (GNL_BUFFER_SIZE + 1),
				READ_CUT_CARAC),
			GNL_BUFFER_SIZE);
		write(1, ft_calloc_char(sizeof(char) * (GNL_BUFFER_SIZE + 1),
				READ_CUT_CARAC),
			GNL_BUFFER_SIZE);
		reset_output();
		if (g_shell.need_pipe)
			fetch_pipe_output();
		waitpid(g_shell.outputmngr, NULL, 0);
		close(g_shell.pipes.to_father[0]);
		close(g_shell.pipes.to_father[1]);
		close(g_shell.pipes.to_son[0]);
		close(g_shell.pipes.to_son[1]);
	}
	g_shell.outputmngr = 0;
}
