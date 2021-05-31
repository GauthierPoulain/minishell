#include "../includes/minishell.h"

static void	check_termcap(char *c, t_reader *reader, char ***str)
{
	if (!ft_strcmp(c, KEY_UP))
		history_before(str, reader);
	else if (!ft_strcmp(c, KEY_DOWN))
		history_after(str, reader);
	else if (!ft_strcmp(c, KEY_RIGHT))
	{
		if (reader->pos < reader->size)
		{
			cursor_op(CURSOR_RIGHT);
			reader->pos++;
		}
	}
	else if (!ft_strcmp(c, KEY_LEFT))
	{
		if (reader->pos > 0)
		{
			cursor_op(CURSOR_LEFT);
			reader->pos--;
		}
	}
}

static bool	check_end(char *c)
{
	if (*c == '\n')
	{
		if (g_shell.use_termcaps)
			ft_putstr(c);
		return (true);
	}
	else if (*c == 4)
	{
		if (g_shell.find_ctrld)
			return (true);
		g_shell.find_ctrld = true;
	}
	else
		g_shell.find_ctrld = false;
	return (false);
}

bool	process_key(char *c, t_reader *reader, char ***str)
{
	char	*key;

	if (check_end(c))
		return (false);
	else if (*c == 127 && reader->pos > 0)
		unprint_char(str, reader);
	else if (*c == 27 && *(c + 1))
	{
		if (PRINT_TERMCAP)
			print_debug_termcap(c + 1);
		check_termcap(c + 1, reader, str);
	}
	else
	{
		key = NULL;
		while (get_this_char(&c, &key) && *key)
			if (ft_isprint(*key))
				print_char(str, key, reader);
		g_shell.history.act_pos = 0;
	}
	return (true);
}
