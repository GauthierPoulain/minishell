#include "../../includes/minishell.h"

void	set_output(t_command cmd)
{
	g_shell.saved_stdout = dup(1);
	g_shell.saved_stderr = dup(2);
	if (pipe(g_shell.pipes.to_father) || pipe(g_shell.pipes.to_son))
		close_shell("pipe error");
	g_shell.outputmngr = fork();
	if (g_shell.outputmngr < 0)
		close_shell("fork error");
	else if (g_shell.outputmngr == 0)
		manage_output(cmd);
	else
	{
		if (cmd.listen_stdout)
			dup2(g_shell.pipes.to_son[1], 1);
		if (cmd.listen_stderr)
			dup2(g_shell.pipes.to_son[1], 2);
	}
}

void	reset_output(void)
{
	dup2(g_shell.saved_stdout, 1);
	dup2(g_shell.saved_stderr, 2);
	close(g_shell.saved_stdout);
	close(g_shell.saved_stderr);
}

static void	loop(t_buffer buff, t_buffer new_buff, t_command cmd)
{
	while (new_buff.size > 0)
	{
		new_buff.size = read(g_shell.pipes.to_son[0], new_buff.ptr,
				GNL_BUFFER_SIZE);
		process_pipe(cmd, buff.ptr, buff.size);
		buff.size = new_buff.size;
		ft_memcpy(buff.ptr, new_buff.ptr, new_buff.size);
	}
}

void	manage_output(t_command cmd)
{
	t_buffer	buff;
	t_buffer	new_buff;

	close(g_shell.pipes.to_son[1]);
	close(g_shell.pipes.to_father[0]);
	if (cmd.need_redirect && !cmd.redirect_append)
		write_redirect(cmd, "", true, 0);
	buff.size = 0;
	new_buff.size = 1;
	buff.ptr = ft_calloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	new_buff.ptr = ft_calloc_char(sizeof(char) * (GNL_BUFFER_SIZE + 1),
			READ_CUT_CARAC);
	ft_putchar_fd(g_shell.pipes.to_father[1], EOF);
	close(g_shell.pipes.to_father[1]);
	loop(buff, new_buff, cmd);
	close(g_shell.pipes.to_son[0]);
	if (cmd.need_pipe)
		write(g_shell.pipes.to_father[1], &g_shell.pipe_output.size, 8);
	if (cmd.need_pipe)
		write(g_shell.pipes.to_father[1], g_shell.pipe_output.ptr,
			g_shell.pipe_output.size);
	close_subprocess(0);
}
