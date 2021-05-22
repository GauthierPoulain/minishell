#include "../../includes/minishell.h"

void	set_output(t_command cmd)
{
	g_shell.saved_stdout = dup(1);
	g_shell.saved_stderr = dup(2);
	if (pipe(g_shell.pipes.to_father) != 0 || pipe(g_shell.pipes.to_son) != 0)
		close_shell("pipe error");
	g_shell.outputmngr = fork();
	if (g_shell.outputmngr < 0)
		close_shell("fork error");
	else if (g_shell.outputmngr == 0)
		manage_output(cmd);
	if (cmd.need_redirect)
	{
		if (cmd.redirect_stdout)
			dup2(g_shell.pipes.to_son[1], 1);
		if (cmd.pipe_stderr)
			dup2(g_shell.pipes.to_son[1], 2);
	}
	else if (cmd.need_pipe)
	{
	}
}

void	reset_output(void)
{
	dup2(g_shell.saved_stdout, 1);
	dup2(g_shell.saved_stderr, 2);
	close(g_shell.saved_stdout);
	close(g_shell.saved_stderr);
}

void	toogle_read_pipe(int code)
{
	(void)code;
	g_shell.read_pipe = false;
}

void	manage_output(t_command cmd)
{
	char	*buffer;

	(void)cmd;
	g_shell.read_pipe = true;
	signal(SIGQUIT, close_subprocess);
	signal(SIGINT, close_subprocess);
	signal(SIGUSR1, toogle_read_pipe);
	while (!g_shell.read_pipe)
		;
	buffer = ft_calloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	ft_putchar_fd(g_shell.pipes.to_father[1], EOF);
	while (read(g_shell.pipes.to_son[0], buffer, GNL_BUFFER_SIZE) > 0
			&& !(!g_shell.read_pipe && ft_strchr(buffer, EOF)))
		process_pipe(buffer);
	process_pipe(buffer);
	close_subprocess(0);
}
