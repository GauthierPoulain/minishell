#include "../../includes/minishell.h"

void	fetch_pipe_output(void)
{
	t_buffer	buff;
	reset_pipe_output();
	buff.ptr = ft_calloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	buff.size = 1;
	while (buff.size > 0)
	{
		printf("fetch output\n");
		buff.size = read(g_shell.pipes.to_father[0], buff.ptr, GNL_BUFFER_SIZE);
		g_shell.pipe_output.ptr = ft_memjoin(g_shell.pipe_output.ptr,
				g_shell.pipe_output.size, buff.ptr, buff.size);
		g_shell.pipe_output.size += buff.size;
	}
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
