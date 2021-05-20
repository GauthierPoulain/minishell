#include "../includes/minishell.h"

void	process_input(char *line)
{
	char	**argv;
	int		tmp;

	tmp = 0;
	line = ft_strreplace(line, "~", get_env("HOME"));
	argv = parse_line(line);
	if (!*argv)
		return ;
	ft_lstclear(&g_shell.tokens);
	if (ft_strlen(line) > 0)
	{
		g_shell.last_return = 0;
		tmp = run_command(argv);
		if (!g_shell.last_return)
			g_shell.last_return = tmp;
	}
}
