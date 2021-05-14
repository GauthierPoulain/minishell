#include "../includes/minishell.h"

static int	exec_builtin(char *prog, char *argv[])
{
	if (!ft_strcmp(prog, "exit"))
		return (close_shell(NULL));
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

static int	exec(char *path, char *argv[])
{
	int	status;

	close(g_shell.pipes.master);
	dup2(g_shell.pipes.slave, 1);
	dup2(g_shell.pipes.slave, 2);
	close(g_shell.pipes.slave);
	execve(path, argv, get_envp());
	status = errno;
	ft_putchar(EOF);
	gc_clean();
	exit(status);
}

int	run_command(char *prog, char *argv[])
{
	pid_t	process;
	char	*path;
	int		status;
	int		pipes[2];
	char	buffer[1024];

	status = 0;
	if (pipe(pipes) != 0)
		close_shell("pipe error");
	g_shell.pipes.slave = pipes[1];
	g_shell.pipes.master = pipes[0];
	reset_input_mode();
	if (!ft_strcmp(which(prog), "builtin"))
		status = exec_builtin(prog, argv);
	else
	{
		path = which(prog);
		if (!path)
		{
			ft_putstr_fd(2, "minishell: command not found: ");
			ft_putstr_fd(2, prog);
			ft_putstr_fd(2, "\n");
			status = 127;
		}
		else
		{
			process = fork();
			if (process == -1)
				close_shell("error while forking subprocess");
			else if (process == 0)
				exec(path, argv);
			else
			{
				close(g_shell.pipes.slave);
				while (read(g_shell.pipes.master, buffer, sizeof(buffer)))
					ft_putcolor(buffer, _MAGENTA);
				close(g_shell.pipes.master);
				wait(&status);
			}
			status = (((status) & 0xff00) >> 8);
		}
	}
	set_input_mode();
	return (status);
}
