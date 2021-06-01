#include "../../includes/minishell.h"

int	exec_builtin(char *prog, char **argv)
{
	if (!ft_strcmp(prog, "exit"))
		return (builtin_exit(argv));
	else if (!ft_strcmp(prog, "cd"))
		return (builtin_cd(argv));
	else if (!ft_strcmp(prog, "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(prog, "env"))
		return (builtin_env(false));
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

void	wait_outputmanager(t_command cmd)
{
	char		buff;

	if (cmd.need_pipe || cmd.need_redirect)
	{
		set_output(cmd);
		while (read(g_shell.pipes.to_father[0], &buff, 1) > 0 && buff != EOF)
			;
	}
}

void	reset_pipe_output(void)
{
	gc_free(g_shell.pipe_output.ptr);
	g_shell.pipe_output.size = 0;
}

void	print_buffer_in_file(t_command *cmd)
{
	if (!cmd->redirect_append)
		write_redirect(cmd->redirect_path, "", true, 0);
	while (g_shell.pipe_output.size > 0)
	{
		if (g_shell.pipe_output.size < GNL_BUFFER_SIZE)
			g_shell.pipe_output.size -= write_redirect(cmd->redirect_path,
					g_shell.pipe_output.ptr, false, g_shell.pipe_output.size);
		else
			g_shell.pipe_output.size -= write_redirect(cmd->redirect_path,
					g_shell.pipe_output.ptr, false, GNL_BUFFER_SIZE);
	}
}

void	print_buffer_in_fd(int fd)
{
	while (g_shell.pipe_output.size > 0)
	{
		if (g_shell.pipe_output.size < GNL_BUFFER_SIZE)
			g_shell.pipe_output.size -= write(fd, g_shell.pipe_output.ptr,
					g_shell.pipe_output.size);
		else
			g_shell.pipe_output.size -= write(fd, g_shell.pipe_output.ptr,
					GNL_BUFFER_SIZE);
	}
	close(fd);
}
