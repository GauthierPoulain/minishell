#include "../../includes/minishell.h"

void	set_output(t_command cmd)
{
	int		pipes[2];

	if (cmd.need_redirect || cmd.need_pipe)
	{
		if (pipe(pipes) != 0)
			close_shell("pipe error");
		g_shell.pipes.target = pipes[0];
		g_shell.pipes.process = pipes[1];
		g_shell.outputmngr = fork();
		if (g_shell.outputmngr < 0)
			close_shell("fork error");
		else if (g_shell.outputmngr == 0)
			manage_output(cmd);
	}
	if (cmd.need_redirect)
	{
		if (cmd.redirect_stdin)
			dup2(g_shell.pipes.process, 1);
		if (cmd.redirect_stdout)
			dup2(g_shell.pipes.process, 2);
	}
	else if (cmd.need_pipe)
	{
	}
}

void	reset_output(void)
{
	dup2(g_shell.saved_stdout, 1);
	dup2(g_shell.saved_stderr, 2);
}

void	manage_output(t_command cmd)
{
	char	*buffer;

	signal(SIGQUIT, close_subprocess);
	signal(SIGINT, close_subprocess);
	(void)cmd;
	close(g_shell.pipes.process);
	buffer = ft_calloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	while (read(g_shell.pipes.target, buffer, GNL_BUFFER_SIZE) > 0
		&& !ft_strchr(buffer, EOF)
		)
		process_pipe(buffer);
	process_pipe(buffer);
	
	gc_free(buffer);
	ft_putstr("done\n");
	close_subprocess(0);
}
