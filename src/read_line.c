#include "../includes/minishell.h"

char	**delete_char(char **str, int pos)
{
	char	**res;
	int		i;

	res = ft_calloc(sizeof(char *) * (ft_tab_len(str) + 2));
	i = 0;
	while (str[i] && i < pos)
	{
		res[i] = str[i];
		i++;
	}
	i++;
	while (str[i])
	{
		res[i - 1] = str[i];
		i++;
	}
	str = res;
	return (res);
}

char	**add_char(char **str, char *c, int pos)
{
	char	**res;
	int		i;

	res = ft_calloc(sizeof(char *) * (ft_tab_len(str) + 2));
	i = 0;
	while (str[i] && i < pos)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = ft_strdup(c);
	while (str[i])
	{
		res[i + 1] = str[i];
		i++;
	}
	str = res;
	return (res);
}

void	unprint_char(char ***str, t_reader *reader)
{
	if (reader->pos < reader->size)
	{
		*str = delete_char(*str, reader->pos - 1);
		cursor_op(CURSOR_LEFT);
		cursor_op(CURSOR_SAVE);
		cursor_op(CURSOR_DEL);
		ft_putstr(get_str_rterm(*str + reader->pos - 1));
		cursor_op(CURSOR_RECOVER);
		tputs(restore_cursor, 1, ft_putchar);
		reader->size--;
		reader->pos--;
	}
	else
	{
		cursor_op(CURSOR_LEFT);
		cursor_op(CURSOR_DEL);
		*str = delete_char(*str, reader->pos - 1);
		reader->size--;
		reader->pos--;
	}
}

void	print_char(char ***str, char *c, t_reader *reader)
{
	if (reader->pos < reader->size)
	{
		*str = add_char(*str, c, reader->pos);
		cursor_op(CURSOR_SAVE);
		ft_putstr(get_str_rterm(*str + reader->pos));
		cursor_op(CURSOR_RECOVER);
		cursor_op(CURSOR_RIGHT);
		reader->size++;
		reader->pos++;
	}
	else
	{
		if (g_shell.use_termcaps)
			ft_putstr(c);
		*str = add_char(*str, c, reader->pos);
		reader->size++;
		reader->pos++;
	}
}

char	*read_term(void)
{
	char		*buffer;
	bool		reading;
	t_reader	reader;
	char		*res;
	int			buffer_len;

	buffer_len = 1;
	if (g_shell.use_termcaps)
		buffer_len = KEY_BUFFER_SIZE;
	buffer = ft_calloc(sizeof(char) * (buffer_len + 1));
	reader.size = 0;
	reader.pos = 0;
	g_shell.actual_str = ft_calloc(sizeof(char *));
	reading = true;
	ft_bzero(buffer, buffer_len + 1);
	while (reading && read(STDIN_FILENO, buffer, buffer_len) >= 0)
	{
		if (!*g_shell.actual_str && *buffer == 4)
			close_shell(NULL);
		reading = process_key(buffer, &reader, &g_shell.actual_str);
		ft_bzero(buffer, buffer_len);
	}
	history_add(g_shell.actual_str);
	res = get_str_rterm(g_shell.actual_str);
	return (res);
}
