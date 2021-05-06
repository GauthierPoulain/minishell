#include "../includes/minishell.h"

static bool	is_a_file(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

char	*which(char *prog)
{
	char	**path;
	char	*prog_path;

	if (is_a_file(prog))
		return (prog);
	path = ft_split(get_env("PATH"), ':');
	while (*path)
	{
		prog_path = ft_strjoin(*path, ft_strjoin("/", prog));
		if (is_a_file(prog_path))
			return (prog_path);
		path++;
	}
	return (NULL);
}

int	builtin_which(char **argv)
{
	char	*prog_path;

	if (!argv[1])
		return (1);
	prog_path = which(argv[1]);
	if (prog_path)
	{
		ft_putstr_fd(1, prog_path);
		ft_putstr_fd(1, "\n");
		return (0);
	}
	else
	{
		ft_putstr_fd(2, argv[1]);
		ft_putstr_fd(2, " not found\n");
		return (1);
	}
}
