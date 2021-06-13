#include "../includes/minishell.h"

char	*get_pwd(void)
{
	char	*cwd;

	cwd = ft_calloc(sizeof(char) * PATH_MAX + 1);
	if (!getcwd(cwd, PATH_MAX))
		print_err("pwd error");
	return (ft_strjoinf1(cwd, ""));
}

int	builtin_pwd(void)
{
	ft_putstr(get_pwd());
	ft_putstr("\n");
	return (0);
}
