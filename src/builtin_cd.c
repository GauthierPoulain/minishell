#include "../includes/minishell.h"

static int	cd_err(int code, char *path)
{
	if (code == 0)
		return (0);
	ft_putstr_fd(2, "cd: ");
	if (code == 1)
	{
		ft_putstr_fd(2, "no such file or directory: ");
		ft_putstr_fd(2, path);
	}
	else if (code == 2)
	{
		ft_putstr_fd(2, "not a directory: ");
		ft_putstr_fd(2, path);
	}
	ft_putstr_fd(2, "\n");
	return (1);
}

static int	check_err(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	else
		close(fd);
	fd = open(path, O_DIRECTORY);
	if (fd == -1)
		return (2);
	else
		close(fd);
	return (0);
}

static void	replace_env(void)
{
	set_env("OLDPWD", get_env("PWD"));
	set_env("PWD", get_pwd());
}

int	builtin_cd(char **argv)
{
	int		ret;
	int		err_code;
	char	*path;

	if (argv[1])
	{
		if (!ft_strcmp(argv[1], "-"))
			path = get_env("OLDPWD");
		else
			path = argv[1];
	}
	else
		path = get_env("HOME");
	err_code = check_err(path);
	if (!err_code)
	{
		ret = chdir(path);
		if (ret == -1)
			cd_err(1, path);
		else
			replace_env();
	}	
	return (cd_err(err_code, path));
}
