#include "../../includes/minishell.h"

void	set_output(t_command cmd)
{
	g_shell.saved_stdout = dup(STDOUT_FILENO);
	g_shell.saved_stderr = dup(STDERR_FILENO);
	if (pipe(g_shell.pipes.to_father) || pipe(g_shell.pipes.to_son))
		print_err("dup2 failure");
	g_shell.outputmngr = fork();
	if (g_shell.outputmngr < 0)
		print_err("fork error");
	else if (g_shell.outputmngr == 0)
		manage_output(cmd);
	else
	{
		if (cmd.listen_stdout && dup2(g_shell.pipes.to_son[1],
				STDOUT_FILENO) == -1)
			print_err("dup2 failure");
		if (cmd.listen_stderr && dup2(g_shell.pipes.to_son[1],
				STDERR_FILENO) == -1)
			print_err("dup2 failure");
	}
}

void	reset_output(void)
{
	if (dup2(g_shell.saved_stdout, STDOUT_FILENO) == -1
		|| dup2(g_shell.saved_stderr, STDERR_FILENO) == -1)
		print_err("dup2 failure");
	close(g_shell.saved_stdout);
	close(g_shell.saved_stderr);
}

static void	loop(t_buffer buff, t_command cmd)
{
	while (g_shell.keep_reading && buff.size > 0)
	{
		buff.size = read(g_shell.pipes.to_son[0], buff.ptr,
				GNL_BUFFER_SIZE);
		process_pipe(cmd, buff.ptr, buff.size);
		ft_bzero(buff.ptr, GNL_BUFFER_SIZE + 1);
	}
}

static void	toggle_reading(int code)
{
	(void)code;
	g_shell.keep_reading = false;
}

void	manage_output(t_command cmd)
{
	t_buffer	buff;

	g_shell.keep_reading = true;
	signal(SIGUSR1, toggle_reading);
	reset_pipe_output();
	close(g_shell.pipes.to_son[1]);
	buff.size = 1;
	buff.ptr = ft_calloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	ft_putchar_fd(g_shell.pipes.to_father[1], EOF);
	loop(buff, cmd);
	close(g_shell.pipes.to_son[1]);
	print_buffer_in_fd(g_shell.pipe_output, g_shell.pipes.to_father[1]);
	close_subprocess(0);
}
