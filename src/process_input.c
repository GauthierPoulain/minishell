#include "../includes/minishell.h"

void	process_input(char *line)
{
	char	**argv;

	line = ft_strreplace(line, "~", get_env("HOME"));
	argv = parse_line(line);
	if (!*argv)
		return ;
	ft_lstclear(&g_shell.tokens);
	if (ft_strlen(line) > 0)
		g_shell.last_return = run_command(argv);
}
