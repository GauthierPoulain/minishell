#include "../includes/minishell.h"

void	file_check_isdir(char *path)
{
	int		fd;

	fd = open(path, O_DIRECTORY);
	if (fd != -1)
	{
		close_shell("error, history path if a directory");
		close(fd);
	}
}

int		history_last_id()
{
	int		fd;
	char	**line;
	int		last;
	char	**tmp;

	file_check_isdir(HISTORY_PATH);
	fd = open(HISTORY_PATH, O_RDONLY);
	if (fd == -1)
		close_shell("error on openning history file");
	line = gc_malloc(sizeof(char *));
	last = 0;
	while (get_next_line(fd, line) > 0)
	{
		tmp = ft_split(*line, ':');
		if (!*tmp)
			last = 0;
		else
			last = ft_atoi(*tmp);
	}
	close(fd);
	return (last);
}

void	history_add(char *line)
{
	int		fd;
	char	*tmp;

	if (ft_strlen(line) < 1)	
		return ;
	file_check_isdir(HISTORY_PATH);
	fd = open(HISTORY_PATH, O_WRONLY | O_CREAT | O_APPEND, 0775);
	if (fd == -1)
		close_shell("error on openning history file");
	tmp = ft_itoa(history_last_id() + 1);
	ft_putstr_fd(fd, tmp);
	ft_putstr_fd(fd, ":");
	ft_putstr_fd(fd, line);
	ft_putstr_fd(fd, "\n");
	close(fd);
}

char	*history_get_at_id(int id)
{
	int		fd;
	char	**line;
	int		last;
	char	**tmp;

	file_check_isdir(HISTORY_PATH);
	fd = open(HISTORY_PATH, O_RDONLY);
	if (fd == -1)
		close_shell("error on openning history file");
	line = gc_malloc(sizeof(char *));
	while (get_next_line(fd, line) > 0)
	{
		tmp = ft_split(*line, ':');
		if (*tmp && !ft_strcmp(!*tmp, ft_itoa(id)))
			return (tmp[1]);
	}
	close(fd);
	return (last);
}

char	*history_before(void)
{
	// if (g_shell.history_id == -1)
		return (history_get_at_id(history_last_id()));
	
}

char	*history_after(void)
{
	// if (g_shell.history_id == -1)
		return (history_get_at_id(history_last_id()));
	
}
