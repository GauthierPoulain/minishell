#include "../../includes/minishell.h"

void	cut_eof(t_buffer *buff)
{
	while (buff->size > 0 && buff->ptr[buff->size - 1] == READ_CUT_CARAC)
	{
		buff->ptr[buff->size - 1] = 0;
		buff->size--;
	}
}

int	exec_builtin(char *prog, char **argv)
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
