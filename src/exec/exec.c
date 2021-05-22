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
	cmd.output = ft_strdup("");
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

void	manage_output(t_command cmd)
{
	char	*buffer;

	signal(SIGQUIT, close_subprocess);
	signal(SIGINT, close_subprocess);
	(void)cmd;
	close(g_shell.pipes.process);
	buffer = ft_calloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	while (read(g_shell.pipes.target, buffer, GNL_BUFFER_SIZE) > 0)
	{
		ft_putcolor(buffer, _BLUE);
		// ft_putstr(buffer);
		ft_bzero(buffer, GNL_BUFFER_SIZE + 1);
	}
	close(g_shell.pipes.target);
	close_subprocess(0);
}

void	set_output(t_command cmd)
{
	int		pipes[2];

	if (cmd.need_redirect || cmd.need_pipe)
	{
		if (pipe(pipes) != 0)
			close_shell("pipe error");
		g_shell.pipes.process = pipes[1];
		g_shell.pipes.target = pipes[0];
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
	if (!ft_strcmp(cmd.path, "builtin"))
		status = exec_builtin(cmd.prog, argv);
	else
	{
		if (!cmd.path)
			status = commant_not_found(cmd.prog);
		else
			subprocess(cmd, &status);
	}
	reset_output();
	add_signals_listeners();
	set_input_mode();
	g_shell.child = 0;
	if (g_shell.outputmngr)
		waitpid(g_shell.outputmngr, NULL, WNOHANG);
	ft_putchar(0);
	g_shell.outputmngr = 0;
	return (status);
}
