#include "../../includes/minishell.h"

int	exec(t_command cmd)
{
	execve(cmd.path, cmd.argv, get_envp());
	return (errno);
}

int	commant_not_found(char *cmd)
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

void	fetch_pipe_output(void)
{
	t_buffer	buffer;

	buffer.ptr = ft_calloc(12);
	read(g_shell.pipes.to_father[0], buffer.ptr, 8);
	buffer.size = *buffer.ptr;
	printf("size = %zu\n", buffer.size);

	buffer.ptr = ft_calloc(sizeof(char) * (buffer.size + 1));
	read(g_shell.pipes.to_father[0], buffer.ptr, buffer.size);
	write(1, buffer.ptr, buffer.size);
}

void	close_pipe(void)
{
	if (g_shell.outputmngr)
	{
		write(1, ft_calloc_char(sizeof(char) * (GNL_BUFFER_SIZE + 1),
				READ_CUT_CARAC),
			GNL_BUFFER_SIZE);
		write(1, ft_calloc_char(sizeof(char) * (GNL_BUFFER_SIZE + 1),
				READ_CUT_CARAC),
			GNL_BUFFER_SIZE);
		reset_output();
		fetch_pipe_output();

		waitpid(g_shell.outputmngr, NULL, 0);
		close(g_shell.pipes.to_father[0]);
		close(g_shell.pipes.to_father[1]);
		close(g_shell.pipes.to_son[0]);
		close(g_shell.pipes.to_son[1]);
	}
	g_shell.outputmngr = 0;
}

int	run_command(char **argv)
{
	t_command	cmd;
	int			status;

	cmd = init_cmd_struct(argv);
	status = 0;
	reset_input_mode();
	wait_outputmanager(cmd);
	if (!ft_strcmp(cmd.path, "builtin"))
		status = exec_builtin(cmd.prog, argv);
	else
	{
		if (!cmd.path)
			status = commant_not_found(cmd.prog);
		else
			subprocess(cmd, &status);
	}
	if (cmd.need_pipe || cmd.need_redirect)
		close_pipe();
	g_shell.child = 0;
	add_signals_listeners();
	set_input_mode();
	return (status);
}
