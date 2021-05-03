#include "../includes/minishell.h"

static bool	is_builtin(char *prog, char **argv)
{
	if (!ft_strcmp(prog, "exit"))
		close_shell(NULL);
	else if (!ft_strcmp(prog, "test"))
		exec_test();
	else if (!ft_strcmp(prog, "cd"))
		g_shell.last_return = builtin_cd(argv);
	else if (!ft_strcmp(prog, "pwd"))
		g_shell.last_return = builtin_pwd();
	else if (!ft_strcmp(prog, "env"))
		g_shell.last_return = builtin_env();
	else if (!ft_strcmp(prog, "echo"))
		g_shell.last_return = builtin_echo(argv);
	else if (!ft_strcmp(prog, "which"))
		g_shell.last_return = builtin_which(argv);
	else
		return (false);
	return (true);
}

void	err_not_fount(char *prog)
{
	ft_putstr_fd(2, "minishell: command not found: ");
	ft_putstr_fd(2, prog);
	ft_putstr_fd(2, "\n");
	g_shell.last_return = 127;
}

void	process_input(char *line)
{
	char	**argv;
	char	*prog;
	char	*prog_path;

	argv = parse_line(line);
	if (!*argv)
		return ;
	prog = argv[0];
	printf("prog = %s\n", prog);
	ft_lstclear(&g_shell.tokens);
	if (ft_strlen(line) < 1)
		return ;
	if (!is_builtin(prog, argv))
	{
		prog_path = which(prog);
		if (prog_path)
			exec_subprocess(prog_path, argv);
		else
			err_not_fount(prog);
	}
}
