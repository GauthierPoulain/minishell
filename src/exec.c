#include "../includes/minishell.h"

static int	exec_builtin(char *prog, char **argv)
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

int	exec_pure(t_command cmd)
{
	execve(cmd.path, cmd.argv, get_envp());
	return (errno);
}

static int	exec(t_command cmd)
{
	int	status;

	// close(g_shell.pipes.master);
	// dup2(g_shell.pipes.slave, 1);
	// dup2(g_shell.pipes.slave, 2);
	// close(g_shell.pipes.slave);
	// execve(path, argv, get_envp());
	// status = errno;
	// ft_putchar(EOF);

	if (!cmd.need_pipe && !cmd.need_redirect)
		status = exec_pure(cmd);
	else
		status = 128;
	gc_clean();
	exit(status);
}

static t_command	init_cmd(char **argv)
{
	t_command	cmd;

	cmd.argv = argv;
	cmd.prog = argv[0];
	cmd.path = which(cmd.prog);
	cmd.need_pipe = false;		//LOOK A THIS MEEEEEEEN
	return (cmd);
}

int	run_command(char **argv)
{
	t_command	cmd;
	int			status;

	cmd = init_cmd(argv);
	status = 0;
	reset_input_mode();
	if (!ft_strcmp(cmd.path, "builtin"))
		status = exec_builtin(cmd.prog, argv);
	else
	{
		if (!cmd.path)
		{
			ft_putstr_fd(g_shell.io.cerr, "minishell: command not found: ");
			ft_putstr_fd(g_shell.io.cerr, cmd.prog);
			ft_putstr_fd(g_shell.io.cerr, "\n");
			status = 127;
		}
		else
		{
			g_shell.child = fork();
			if (g_shell.child < 0)
				close_shell("fork error");
			else if (g_shell.child == 0)
			{
				signal(SIGQUIT, exit);
				signal(SIGINT, exit);
				exec(cmd);
			}
			else
			{
				signals_listeners_to_child();
				wait(&status);
				status = (((status) & 0xff00) >> 8);
			}
		}
	}
	add_signals_listeners();
	set_input_mode();
	return (status);
}

// int	run_command(char **argv)
// {
// 	pid_t		process;
// 	t_command	cmd;
// 	int			status;
// 	int			pipes[2];
// 	char		buffer[1024];

// 	cmd = init_cmd(argv);
// 	status = 0;
// 	if (pipe(pipes) != 0)
// 		close_shell("pipe error");
// 	g_shell.pipes.slave = pipes[1];
// 	g_shell.pipes.master = pipes[0];
// 	reset_input_mode();
// 	if (!ft_strcmp(cmd.path, "builtin"))
// 		status = exec_builtin(cmd.prog, argv);
// 	else
// 	{
// 		if (!cmd.path)
// 		{
// 			ft_putstr_fd(2, "minishell: command not found: ");
// 			ft_putstr_fd(2, cmd.prog);
// 			ft_putstr_fd(2, "\n");
// 			status = 127;
// 		}
// 		else
// 		{
// 			process = fork();
// 			if (process == -1)
// 				close_shell("fork error");
// 			else if (process == 0)
// 				exec(cmd.path, argv);
// 			else
// 			{
// 				close(g_shell.pipes.slave);
// 				while (read(g_shell.pipes.master, buffer, sizeof(buffer)))
// 										printf("buffer = %s\n", buffer)			<<<<<<<<<----------- need to (speeeed) check this
// 					ft_putcolor(buffer, _MAGENTA);
// 				close(g_shell.pipes.master);
// 				wait(&status);
// 				status = (((status) & 0xff00) >> 8);
// 			}
// 		}
// 	}
// 	set_input_mode();
// 	return (status);
// }
