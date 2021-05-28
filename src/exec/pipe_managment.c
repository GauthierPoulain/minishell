#include "../../includes/minishell.h"

void	fetch_pipe_output(void)
{
	t_buffer	buffer;

	buffer.ptr = ft_calloc(12);
	read(g_shell.pipes.to_father[0], buffer.ptr, 8);
	buffer.size = *buffer.ptr;
	printf("size = %zu\n", buffer.size);
	buffer.ptr = ft_calloc(sizeof(char) * (buffer.size + 1));
	read(g_shell.pipes.to_father[0], buffer.ptr, buffer.size);
	write(1, buffer.ptr, buffer.size);
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
		fetch_pipe_output();
		waitpid(g_shell.outputmngr, NULL, 0);
		close(g_shell.pipes.to_father[0]);
		close(g_shell.pipes.to_father[1]);
		close(g_shell.pipes.to_son[0]);
		close(g_shell.pipes.to_son[1]);
	}
	g_shell.outputmngr = 0;
}
