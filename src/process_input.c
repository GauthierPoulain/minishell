#include "../includes/minishell.h"

static void	preexec(char **argv)
{
	(void)argv;
	return ;
}

static void	precmd(void)
{
	return ;
}

void	process_input(char *line)
{
	char	**argv;
	char	*prog;

	replace_env_line(&line);
	argv = ft_split_spaces(line);
	prog = argv[0];
	preexec(argv);
	if (ft_strlen(line) < 1)
		return ;
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
	else
	{
		ft_putstr_fd(2, "minishell: command not found: ");
		ft_putstr_fd(2, prog);
		ft_putstr_fd(2, "\n");
		g_shell.last_return = 127;
	}
	precmd();
}
