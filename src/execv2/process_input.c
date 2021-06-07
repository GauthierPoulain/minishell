#include "../../includes/minishell.h"

void	run_subprocess(t_command cmd)
{
	int	fd;

	signal(SIGQUIT, close_subprocess);
	signal(SIGINT, close_subprocess);
	signal(SIGTERM, close_subprocess);
	if (cmd.need_pipe || cmd.need_redirect)
	{
		fd = open("/dev/tty", O_RDWR);
		ioctl(fd, TIOCNOTTY, NULL);
		close(fd);
	}
	// if (read_pipe)
	// {
	// 	close(pipes[1]);
	// 	if (dup2(pipes[0], STDIN_FILENO) == -1)
	// 		close_shell("dup2 failure");
	// }
	execve(cmd.path, cmd.argv, get_envp());
	close_subprocess(errno);
}

int	handle_subprocess(t_command cmd)
{
	int	status;

	status = 0;
	g_shell.child = fork();
	if (g_shell.child < 0)
		close_shell("fork error");
	else if (g_shell.child == 0)
		run_subprocess(cmd);
	else
	{
		signals_listeners_to_child();
		waitpid(g_shell.child, &status, 0);
	}
	return (((status) & 0xff00) >> 8);
}

void	run_command(t_command cmd, int *status)
{
	*status = 0;
	if (!ft_strcmp(cmd.path, "builtin"))
		*status = exec_builtin(cmd.prog, cmd.argv);
	else if (cmd.path)
		*status = handle_subprocess(cmd);
	else
		*status = commant_not_found(cmd.prog);
}

void	get_command(t_command *cmd, char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i + 1])
		i++;
	if (is_operator(line + i))
	{
		cmd->operator = ft_strdup(line + i);
		line[i] = 0;
	}
	ft_lstclear(&g_shell.tokens);
	cmd->argv = parse_line(line);
	cmd->prog = cmd->argv[0];
	cmd->path = which(cmd->prog);
}

void	process_input(char *line)
{
	t_list		*cmds;
	t_command	cmd;
	int			status;
	
	cmds = split_commands(line);
	if (!cmds)
		g_shell.last_return = syntax_error();

	// line = ft_strreplace(line, "~", get_env("HOME")); FAUT LE GERER AILLEUR CA

	// split command
	// loop in commands
	// parsing
	// replace env var
	// exec
	// end loop
	
	if (!line)
		return ;
	g_shell.pipe_output.ptr = NULL;
	g_shell.is_running = true;
	reset_input_mode();
	while (cmds)
	{
		g_shell.last_return = 0;
		get_command(&cmd, cmds->content);
		run_command(cmd, &status);
		if (!g_shell.last_return)
			g_shell.last_return = status;
		cmds = cmds->next;
		add_signals_listeners();
	}
	g_shell.is_running = false;
	set_input_mode();
}
