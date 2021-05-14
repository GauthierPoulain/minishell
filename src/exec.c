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

static int	exec(char *path, char *prog, char *argv[])
{
	int	status;

	if (!path)
	{
		ft_putstr_fd(2, "minishell: command not found: ");
		ft_putstr_fd(2, prog);
		ft_putstr_fd(2, "\n");
		status = 127;
	}
	else
	{
		execve(path, argv, get_envp());
		status = errno;
	}
	gc_clean();
	exit(status);
}

int	run_command(char *prog, char *argv[])
{
	pid_t	process;
	int		status;

	status = 0;
	reset_input_mode();
	if (!ft_strcmp(which(prog), "builtin"))
	{
		status = exec_builtin(prog, argv);
		set_input_mode();
		return (status);
	}
	else
	{
		process = fork();
		if (process == -1)
			close_shell("error while forking subprocess");
		else if (process == 0)
			exec(which(prog), prog, argv);
		else
			wait(&status);
		set_input_mode();
		return (((status) & 0xff00) >> 8);
	}
}
