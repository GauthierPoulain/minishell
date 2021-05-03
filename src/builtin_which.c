#include "../includes/minishell.h"

static bool	is_a_programm(char *path)
{
	int		fd;

	fd = open(path, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (false);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

char	*which(char *prog)
{
	char	**path;
	char	*prog_path;

	path = ft_split(get_env("PATH"),  ':');
	while (*path)
	{
		prog_path = ft_strjoin(*path, ft_strjoin("/", prog));
		if (is_a_programm(prog_path))
			return (prog_path);
		path++;
	}
	return (NULL);
}
