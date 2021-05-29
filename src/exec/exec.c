#include "../../includes/minishell.h"

static void	subprocess_exec(t_command cmd, int pipes[2])
{
	int	fd;

	close(pipes[1]);
	if (g_shell.pipe_output.ptr)
		dup2(pipes[0], STDIN_FILENO);
	if (cmd.file_input)
	{
		fd = open(cmd.redirect_path, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd(2, "can't open input file\n");
			close_subprocess(1);
		}
		dup2(fd, STDIN_FILENO);
	}
	signal(SIGQUIT, close_subprocess);
	signal(SIGINT, close_subprocess);
	execve(cmd.path, cmd.argv, get_envp());
	close(pipes[0]);
	close_subprocess(errno);
}

static void	subprocess(t_command cmd, int *status)
{
	int	pipes[2];

	if (g_shell.pipe_output.ptr)
		if (pipe(pipes) != 0)
			close_shell("pipe error");
	g_shell.child = fork();
	if (g_shell.child < 0)
		close_shell("fork error");
	else if (g_shell.child == 0)
		subprocess_exec(cmd, pipes);
	else
	{
		signals_listeners_to_child();
		if (g_shell.pipe_output.ptr)
		{
			close(pipes[0]);
			write(pipes[1], g_shell.pipe_output.ptr, g_shell.pipe_output.size);
			close(pipes[1]);
		}
		wait(status);
		*status = (((*status) & 0xff00) >> 8);
	}
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
			subprocess(*cmd, status);
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

	cmds = get_commands(argv);
	if (!cmds)
		return (syntax_error());
	reset_input_mode();
	while (cmds)
	{
		cmd = cmds->content;
		if (!cmd->skip_exec)
			run_command(cmd, &status);
		cmds = cmds->next;
	}
	add_signals_listeners();
	set_input_mode();
	return (status);
}
