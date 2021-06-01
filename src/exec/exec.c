#include "../../includes/minishell.h"

t_buffer	*get_multiple_input(t_command cmd)
{
	t_buffer	*res;

	res = gc_malloc(sizeof(t_buffer));
	res->ptr = NULL;
	res->size = 0;
	if (g_shell.pipe_output.ptr)
	{
		res->ptr = ft_calloc(sizeof(char) * g_shell.pipe_output.size);
		res->ptr = ft_memjoin(res->ptr, res->size, g_shell.pipe_output.ptr,
				g_shell.pipe_output.size);
		res->size += g_shell.pipe_output.size;
	}
	if (cmd.redirect_path && is_a_file(cmd.redirect_path))
		get_input_part2(cmd, res);
	return (res);
}

static void	subprocess_exec(t_command cmd, int pipes[2], bool read_pipe)
{
	int	fd;

	signal(SIGQUIT, close_subprocess);
	signal(SIGINT, close_subprocess);
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

static void	subprocess(t_command cmd, int *status)
{
	int			pipes[2];
	t_buffer	*data;
	bool		read_pipe;

	if (pipe(pipes))
		close_shell("pipe error");
	data = get_multiple_input(cmd);
	read_pipe = data->size > 0;
	g_shell.child = fork();
	if (g_shell.child < 0)
		close_shell("fork error");
	else if (g_shell.child == 0)
		subprocess_exec(cmd, pipes, read_pipe);
	else
	{
		signals_listeners_to_child();
		if (read_pipe)
		{
			write(pipes[1], data->ptr, data->size);
			close(pipes[1]);
		}
		reset_pipe_output();
		wait(status);
		*status = (((*status) & 0xff00) >> 8);
	}
}

void	run_command(t_command *cmd, int *status, t_list *lst)
{
	*status = 0;
	g_shell.need_pipe = cmd->need_pipe;
	wait_outputmanager(*cmd, lst);
	if (!ft_strcmp(cmd->path, "builtin"))
		*status = exec_builtin(cmd->prog, cmd->argv);
	else
	{
		if (!cmd->path)
			*status = commant_not_found(cmd->prog);
		else
			subprocess(*cmd, status);
	}
	if (cmd->need_pipe || cmd->need_redirect)
		close_pipe();
	g_shell.child = 0;
}

int	run_line(char **argv)
{
	t_list		*cmds;
	t_command	*cmd;
	int			status;

	cmds = get_commands(argv);
	if (!cmds)
		return (syntax_error());
	reset_input_mode();
	status = 0;
	while (cmds && !status)
	{
		cmd = cmds->content;
		if (!cmd->skip_exec)
			run_command(cmd, &status, cmds);
		cmds = cmds->next;
	}
	add_signals_listeners();
	set_input_mode();
	return (status);
}
