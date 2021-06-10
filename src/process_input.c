#include "../includes/minishell.h"

void	process_input(char *line)
{
	t_ptoken	*argv;
	int			tmp;

	tmp = 0;
	if (!line || ft_strlen(ft_strtrim_spaces(line)) <= 0)
		return ;
	argv = parse_line(line);
	if (!argv)
		return ;
	ft_lstclear(&g_shell.tokens);
	if (ft_strlen(line) > 0)
		run_line(argv);
}
