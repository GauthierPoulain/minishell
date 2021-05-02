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

int	history_last_id(int max)
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
	last = 1;
	while (get_next_line(fd, line) > 0)
	{
		tmp = ft_split(*line, ':');
		if (*tmp)
			if (ft_atoi(*tmp) > last && (max == -1 || ft_atoi(*tmp) < max))
				last = ft_atoi(*tmp);
		gc_free(*line);
	}
	close(fd);
	return (last);
}

int	history_first_id(int min)
{
	int		fd;
	char	**line;
	int		first;
	char	**tmp;

	file_check_isdir(HISTORY_PATH);
	fd = open(HISTORY_PATH, O_RDONLY);
	if (fd == -1)
		close_shell("error on openning history file");
	line = gc_malloc(sizeof(char *));
	first = history_last_id(-1);
	while (get_next_line(fd, line) > 0)
	{
		tmp = ft_split(*line, ':');
		if (*tmp)
			if (ft_atoi(*tmp) < first && (min == -1 || ft_atoi(*tmp) > min))
				first = ft_atoi(*tmp);
		gc_free(*line);
	}
	close(fd);
	return (first);
}

void	history_add(char *line)
{
	int		fd;
	char	*tmp;

	file_check_isdir(HISTORY_PATH);
	fd = open(HISTORY_PATH, O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (fd == -1)
		close_shell("error on openning history file");
	if (ft_strlen(line) < 1)
	{
		close(fd);
		return ;
	}
	tmp = ft_itoa(history_last_id(g_shell.history_id) + 1);
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
	char	**tmp;

	file_check_isdir(HISTORY_PATH);
	fd = open(HISTORY_PATH, O_RDONLY);
	if (fd == -1)
		close_shell("error on openning history file");
	line = gc_malloc(sizeof(char *));
	while (get_next_line(fd, line) > 0)
	{
		tmp = ft_split(*line, ':');
		if (*tmp && !ft_strcmp(*tmp, ft_itoa(id)))
		{
			g_shell.history_id = id;
			close(fd);
			return (tmp[1]);
		}
		gc_free(*line);
	}
	close(fd);
	return (NULL);
}

char	*history_before(void)
{
	return (history_get_at_id(history_last_id(g_shell.history_id)));
}

char	*history_after(void)
{
	return (history_get_at_id(history_first_id(g_shell.history_id)));
}
