#include "../../includes/minishell.h"

static int	exec_builtin(char *prog, char **argv)
{
	if (!ft_strcmp(prog, "exit"))
		return (builtin_exit(argv));
	else if (!ft_strcmp(prog, "cd"))
		return (builtin_cd(argv));
	else if (!ft_strcmp(prog, "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(prog, "env"))
		return (builtin_env());
	else if (!ft_strcmp(prog, "echo"))
		return (builtin_echo(argv));
	else if (!ft_strcmp(prog, "which"))
		return (builtin_which(argv));
	else if (!ft_strcmp(prog, "export"))
		return (builtin_export(argv));
	else if (!ft_strcmp(prog, "unset"))
		return (builtin_unset(argv));
	else
		return (1);
}

int	exec(t_command cmd)
{
	execve(cmd.path, cmd.argv, get_envp());
	return (errno);
}

static t_command	init_cmd(char **argv)
{
	t_command	cmd;

	cmd.argv = argv;
	cmd.prog = argv[0];
	cmd.path = which(cmd.prog);
	cmd.need_pipe = false;
	cmd.need_redirect = true;
	cmd.redirect_stdin = true;
	cmd.redirect_stdout = true;
	return (cmd);
}

int		commant_not_found(char *cmd)
{
	ft_putstr_fd(2, "minishell: command not found: ");
	ft_putstr_fd(2, cmd);
	ft_putstr_fd(2, "\n");
	return (127);
}

static void	subprocess(t_command cmd, int *status)
{
	g_shell.child = fork();
	if (g_shell.child < 0)
		close_shell("fork error");
	else if (g_shell.child == 0)
	{
		signal(SIGQUIT, close_subprocess);
		signal(SIGINT, close_subprocess);
		exec(cmd);
	}
	else
	{
		signals_listeners_to_child();
		wait(status);
		*status = (((*status) & 0xff00) >> 8);
	}
}

void	cut_eof(char *str)
{
	char	*pos;

	pos = ft_strchr(str, EOF);
	if (pos)
		*pos = 0;
}

void	process_buffer(char *buffer)
{
	// print_debug_termcap(buffer);
	cut_eof(buffer);
	ft_putcolor(buffer, _BLUE);
	ft_bzero(buffer, GNL_BUFFER_SIZE + 1);
}

void	manage_output(t_command cmd)
{
	char	*buffer;

	signal(SIGQUIT, close_subprocess);
	signal(SIGINT, close_subprocess);
	(void)cmd;
	close(g_shell.pipes.process);
	buffer = ft_calloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	while (read(g_shell.pipes.target, buffer, GNL_BUFFER_SIZE) > 1 && !ft_strchr(buffer, EOF))
		process_buffer(buffer);
	process_buffer(buffer);
	gc_free(buffer);
	ft_putstr("done\n");
	close_subprocess(0);
}

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

int	run_command(char **argv)
{
	t_command	cmd;
	int			status;

	cmd = init_cmd(argv);
	status = 0;
	reset_input_mode();
	set_output(cmd);
	close(g_shell.pipes.target);
	if (!ft_strcmp(cmd.path, "builtin"))
		status = exec_builtin(cmd.prog, argv);
	else
	{
		if (!cmd.path)
			status = commant_not_found(cmd.prog);
		else
			subprocess(cmd, &status);
	}
	g_shell.child = 0;
	if (g_shell.outputmngr)
	{
		ft_putchar(EOF);
		waitpid(g_shell.outputmngr, NULL, 0);
		close(g_shell.pipes.process);
	}
	reset_output();
	g_shell.outputmngr = 0;
	add_signals_listeners();
	set_input_mode();
	return (status);
}
