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

void	history_add(char *line)
{
	int		fd;

	file_check_isdir(HISTORY_PATH);
	fd = open(HISTORY_PATH, O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (fd == -1)
		close_shell("error on openning history file");
	if (ft_strlen(line) < 1)
	{
		close(fd);
		return ;
	}
	ft_putstr_fd(fd, line);
	ft_putstr_fd(fd, "\n");
	close(fd);
}

void	read_history(void)
{
	int		fd;
	char	**line;

	ft_lstclear(&g_shell.history.lst);
	file_check_isdir(HISTORY_PATH);
	g_shell.history.lst = NULL;
	fd = open(HISTORY_PATH, O_RDONLY);
	if (fd == -1)
		close_shell("error on openning history file");
	line = gc_malloc(sizeof(char *));
	while (get_next_line(fd, line) > 0)
	{
		if (*line)
			ft_lstadd_front(&g_shell.history.lst, ft_lstnew(ft_strdup(*line)));
		gc_free(*line);
	}
	ft_lstadd_front(&g_shell.history.lst, ft_lstnew(NULL));
	close(fd);
}

char	*get_in_history(int pos)
{
	int		id;
	t_list	*lst;

	lst = g_shell.history.lst;
	id = 0;
	while (lst)
	{
		if (id == pos)
			return (lst->content);
		id++;
		lst = lst->next;
	}
	return (NULL);
}

void	remove_line(char ***str, t_reader *reader)
{
	t_reader	tmp_reader;

	// void	unprint_char(char ***str, t_reader *reader)
	while (**str)
	{
		tmp_reader.pos = ft_tab_len(*str);
		tmp_reader.size = ft_tab_len(*str);
		unprint_char(str, &tmp_reader);
		// tputs(cursor_right, 1, ft_putchar);
	}
	reader->pos = 0;
	reader->size = 0;
}

void	put_in_term(char *line, char ***str, t_reader *reader)
{
	char		*c;

	c = gc_malloc(sizeof(char) * 2);
	c[1] = 0;
	while (*line)
	{
		c[0] = *line;
		print_char(str, c, reader);
		// tputs(save_cursor, 1, ft_putchar);
		// write(0, line, 1);
		// tputs(restore_cursor, 1, ft_putchar);
		// tputs(cursor_right, 1, ft_putchar);
		line++;
	}
	
}

char	*history_before(char ***str, t_reader *reader)
{
	int		id;
	char	*res;

	id = g_shell.history.act_pos + 1;
	if (id > (int)ft_lstsize(g_shell.history.lst) - 1)
		id = (int)ft_lstsize(g_shell.history.lst) - 1;
	res = get_in_history(id);
	g_shell.history.act_pos = id;
	remove_line(str, reader);
	put_in_term(res, str, reader);
	return (NULL);
}

char	*history_after(char ***str, t_reader *reader)
{
	int		id;
	char	*res;

	id = g_shell.history.act_pos - 1;
	if (id < 0)
		id = 0;
	res = get_in_history(id);
	g_shell.history.act_pos = id;
	remove_line(str, reader);
	put_in_term(res, str, reader);
	return (NULL);
}
