#include "../../includes/minishell.h"

static void	subprocess_exec(t_command cmd, int pipes[2], bool read_pipe)
{
	int	fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd.need_pipe || cmd.need_redirect)
	{
		fd = open("/dev/tty", O_RDWR);
		ioctl(fd, TIOCNOTTY, NULL);
		close(fd);
	}
	if (read_pipe)
	{
		close(pipes[1]);
		if (dup2(pipes[0], STDIN_FILENO) == -1)
			print_err("dup2 failure");
	}
	execve(cmd.path, cmd.argv, get_envp());
	close_subprocess(errno);
}

static int	subprocess(t_command cmd)
{
	int			pipes[2];
	t_buffer	*data;
	bool		read_pipe;

	if (cmd.file_input && !is_a_file(cmd.redirect_path))
		return (file_not_found(cmd.redirect_path));
	if (pipe(pipes))
		print_err("pipe failure");
	data = get_multiple_input(cmd);
	read_pipe = data->ptr != 0;
	g_shell.child = fork();
	if (g_shell.child < 0)
		print_err("fork failure");
	else if (g_shell.child == 0)
		subprocess_exec(cmd, pipes, read_pipe);
	else
		return (child_supervisor(data, read_pipe, pipes));
	return (0);
}

int	run_command(t_command *cmd)
{
	int	status;

	g_shell.need_pipe = cmd->need_pipe;
	wait_outputmanager(*cmd);
	if (!ft_strcmp(cmd->path, "builtin"))
		status = exec_builtin(cmd->prog, cmd->argv);
	else
	{
		if (!cmd->path)
			status = commant_not_found(cmd->prog);
		else
			status = subprocess(*cmd);
	}
	if (cmd->need_pipe || cmd->need_redirect)
		close_pipe();
	reset_pipe_output();
	g_shell.child = 0;
	return (status);
}

void	loop(t_list *cmds)
{
	t_command	*cmd;
	bool		nxt;

	nxt = true;
	while (nxt && cmds)
	{
		cmd = cmds->content;
		cmd->argv = get_argv(cmd->token);
		if (cmd->argv)
			cmd->prog = cmd->argv[0];
		else
			cmd->prog = ft_strdup("");
		cmd->path = which(cmd->prog);
		nxt = fill_cmd_structs(cmd, cmds);
		if (nxt)
		{
			if (!cmd->skip_exec)
				g_shell.last_return = run_command(cmd);
			check_write_redirect(cmd, cmds);
		}
		cmds = cmds->next;
	}
}

void	run_line(t_ptoken *argv)
{
	t_list		*cmds;

	g_shell.pipe_output.ptr = NULL;
	g_shell.is_running = true;
	cmds = get_commands(argv);
	if (cmds && cmds->content && ((t_command *)cmds->content)->token)
		(((t_command *)cmds->content)->token)->spaces = 1;
	reset_input_mode();
	if (!cmds)
		g_shell.last_return = syntax_error();
	else
		loop(cmds);
	g_shell.is_running = false;
	add_signals_listeners();
	set_input_mode();
}
