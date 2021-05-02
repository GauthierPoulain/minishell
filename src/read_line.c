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
		tputs(cursor_left, 1, ft_putchar);
		tputs(save_cursor, 1, ft_putchar);
		ft_putstr(get_str_rterm(*str + reader->pos - 1));
		ft_putstr(" ");
		tputs(restore_cursor, 1, ft_putchar);
		reader->size--;
		reader->pos--;
	}
	else
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
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
		tputs(save_cursor, 1, ft_putchar);
		ft_putstr(get_str_rterm(*str + reader->pos));
		tputs(restore_cursor, 1, ft_putchar);
		tputs(cursor_right, 1, ft_putchar);
		reader->size++;
		reader->pos++;
	}
	else
	{
		ft_putstr(c);
		*str = add_char(*str, c, reader->pos);
		reader->size++;
		reader->pos++;
	}
}

char	*read_term(void)
{
	char		buffer[KEY_BUFFER_SIZE + 1];
	bool		reading;
	t_reader	reader;
	char		**str;
	char		*res;

	reader.size = 0;
	reader.pos = 0;
	str = ft_calloc(sizeof(char *));
	reading = true;
	ft_bzero(buffer, KEY_BUFFER_SIZE + 1);
	while (reading && read(STDIN_FILENO, buffer, KEY_BUFFER_SIZE) >= 0)
	{
		reading = process_key(buffer, &reader, &str);
		ft_bzero(buffer, KEY_BUFFER_SIZE);
	}
	res = get_str_rterm(str);
	gc_free_tab(str);
	return (res);
}
