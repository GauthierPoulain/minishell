#include "../../includes/minishell.h"

static void	subprocess_exec(t_command cmd, int pipes[2], bool read_pipe)
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
	if (read_pipe)
	{
		close(pipes[1]);
		dup2(pipes[0], STDIN_FILENO);
	}
	execve(cmd.path, cmd.argv, get_envp());
	close_subprocess(errno);
}

int	child_supervisor(t_buffer *data, bool read_pipe, int pipes[2])
{
	int			status;

	signals_listeners_to_child();
	if (read_pipe)
		print_buffer_in_fd(*data, pipes[1]);
	reset_pipe_output();
	waitpid(g_shell.child, &status, 0);
	close(pipes[0]);
	close(pipes[1]);
	return (((status) & 0xff00) >> 8);
}

static int	subprocess(t_command cmd)
{
	int			pipes[2];
	t_buffer	*data;
	bool		read_pipe;

	if (cmd.file_input && !is_a_file(cmd.redirect_path))
		return (file_not_found(cmd.redirect_path));
	if (pipe(pipes))
		close_shell("pipe error");
	data = get_multiple_input(cmd);
	read_pipe = data->ptr != 0;
	g_shell.child = fork();
	if (g_shell.child < 0)
		close_shell("fork error");
	else if (g_shell.child == 0)
		subprocess_exec(cmd, pipes, read_pipe);
	else
		return (child_supervisor(data, read_pipe, pipes));
	return (0);
}

void	run_command(t_command *cmd, int *status)
{
	*status = 0;
	g_shell.need_pipe = cmd->need_pipe;
	wait_outputmanager(*cmd);
	if (!ft_strcmp(cmd->path, "builtin"))
		*status = exec_builtin(cmd->prog, cmd->argv);
	else
	{
		if (!cmd->path)
			*status = commant_not_found(cmd->prog);
		else
			*status = subprocess(*cmd);
	}
	reset_pipe_output();
	if (cmd->need_pipe || cmd->need_redirect)
		close_pipe();
	g_shell.child = 0;
}

int	run_line(char **argv)
{
	t_list		*cmds;
	t_command	*cmd;
	int			status;

	g_shell.pipe_output.ptr = NULL;
	g_shell.is_running = true;
	cmds = get_commands(argv);
	if (!cmds)
		return (syntax_error());
	reset_input_mode();
	status = 0;
	while (cmds)
	{
		cmd = cmds->content;
		if (!cmd->skip_exec)
			run_command(cmd, &status);
		check_write_redirect(cmd, cmds);
		cmds = cmds->next;
	}
	g_shell.is_running = false;
	add_signals_listeners();
	set_input_mode();
	return (status);
}
