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
		if (cmd.redirect_stderr)
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
	int		len;

	g_shell.read_pipe = true;
	if (cmd.need_redirect)
		write_redirect(cmd, "", true, 0);
	signal(SIGQUIT, toogle_read_pipe);
	signal(SIGINT, toogle_read_pipe);
	signal(SIGUSR1, toogle_read_pipe);
	buffer = ft_calloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	ft_putchar_fd(g_shell.pipes.to_father[1], EOF);
	len = GNL_BUFFER_SIZE;
	while (len == GNL_BUFFER_SIZE || g_shell.read_pipe)
	{
		len = read(g_shell.pipes.to_son[0], buffer, GNL_BUFFER_SIZE);
		if (!g_shell.read_pipe && len < GNL_BUFFER_SIZE)
			len--;
		process_pipe(cmd, buffer, len);
	}
	close_subprocess(0);
}
