#include "../includes/minishell.h"

int	get_this_char(char **c, char **retour)
{
	char	*res;

	if (!*c)
		*retour = NULL;
	else
	{
		res = ft_calloc(sizeof(char) * 2);
		if ((0x80 & **c) == 0)
		{
			res = ft_strjoinc(res, **c);
			*c += 1;
			*retour = res;
		}
		else
		{
			while ((0x80 & **c) != 0)
			{
				res = ft_strjoinc(res, **c);
				*c += 1;
			}
			*retour = res;
		}
	}
	return (1);
}

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

bool	process_key(char *c, t_reader *reader, char ***str)
{
	char	*key;

	if (*c == '\n')
	{
		if (g_shell.use_termcaps)
			ft_putstr(c);
		return (false);
	}
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

char	*get_str_rterm(char **str)
{
	char	*res;

	res = ft_strdup("");
	if (!str)
		return (NULL);
	while (*str)
	{
		res = ft_strjoinf1(res, *str);
		str++;
	}
	return (res);
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
