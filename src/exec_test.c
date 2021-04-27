#include "../includes/minishell.h"

void	exec_test(void)
{
	char	*prog = "/bin/ls";
	char	*argv[] = {prog, "/bin", NULL};

	sleep(2);
	g_shell.last_return = exec_subprocess(prog, argv);
}

// void	exec_test(void)
// {
// 	char	**envp;

// 	envp = get_envp();
// 	while (*envp)
// 	{
// 		ft_putstr(*envp);
// 		envp++;
// 	}
// }
