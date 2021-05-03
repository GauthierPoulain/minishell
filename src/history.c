#include "../includes/minishell.h"

void	history_add(char **line)
{
	g_shell.history.lst->content = line;
	ft_lstadd_front(&g_shell.history.lst, ft_lstnew(NULL));
}

char	**get_in_history(int pos)
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

	while (**str)
	{
		tmp_reader.pos = ft_tab_len(*str);
		tmp_reader.size = ft_tab_len(*str);
		unprint_char(str, &tmp_reader);
	}
	reader->pos = 0;
	reader->size = 0;
}

void	put_in_term(char **line, char ***str, t_reader *reader)
{
	if (line)
	{
		while (*line)
		{
			print_char(str, *line, reader);
			line++;
		}
	}
}

char	*history_before(char ***str, t_reader *reader)
{
	int		id;
	char	**res;

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
	char	**res;

	id = g_shell.history.act_pos - 1;
	if (id < 0)
		id = 0;
	res = get_in_history(id);
	g_shell.history.act_pos = id;
	remove_line(str, reader);
	put_in_term(res, str, reader);
	return (NULL);
}
