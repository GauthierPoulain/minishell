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

void	print_buffer_in_file(t_command *cmd, bool print)
{
	t_buffer	cpy;

	cpy.ptr = g_shell.pipe_output.ptr;
	cpy.size = g_shell.pipe_output.size;
	if (!cmd->redirect_append)
		write_redirect(cmd->redirect_path, "", true, 0);
	while (print && cpy.size > 0)
	{
		if (cpy.size < GNL_BUFFER_SIZE)
		{
			cpy.size -= write_redirect(cmd->redirect_path, cpy.ptr,
					false, cpy.size);
			cpy.ptr += cpy.size;
		}
		else
		{
			cpy.size -= write_redirect(cmd->redirect_path, cpy.ptr,
					false, GNL_BUFFER_SIZE);
			cpy.ptr += GNL_BUFFER_SIZE;
		}
	}
}

void	print_buffer_in_fd(t_buffer buff, int fd)
{
	t_buffer	cpy;
	bool		stop;

	stop = false;
	cpy.ptr = buff.ptr;
	cpy.size = buff.size;
	while (!stop && cpy.size >= 0)
	{
		if (cpy.size < GNL_BUFFER_SIZE)
		{
			cpy.size -= write(fd, cpy.ptr, cpy.size);
			cpy.ptr += cpy.size;
			stop = true;
		}
		else
		{
			cpy.size -= write(fd, cpy.ptr, GNL_BUFFER_SIZE);
			cpy.ptr += GNL_BUFFER_SIZE;
		}
	}
	close(fd);
}
