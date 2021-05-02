#include "../includes/minishell.h"

static void	print_debug_termcap(char *c)
{
	printf("new key\n");
	printf("key = %d, char = %c\n", c[0], c[0]);
	printf("key = %d, char = %c\n", c[1], c[1]);
	printf("key = %d, char = %c\n", c[2], c[2]);
	printf("key = %d, char = %c\n", c[3], c[3]);
	printf("key = %d, char = %c\n", c[4], c[4]);
	printf("key = %d, char = %c\n", c[5], c[5]);
	printf("key = %d, char = %c\n", c[6], c[6]);
	printf("key = %d, char = %c\n", c[7], c[7]);
	printf("key = %d, char = %c\n", c[8], c[8]);
	printf("key = %d, char = %c\n", c[9], c[9]);
	printf("key = %d, char = %c\n", c[10], c[10]);
	printf("done\n");
}

// [A : up arrow
// [B : down arrow
// [C : right arrow
// [D : left arrow

static void	check_termcap(char *c, t_reader *reader)
{
	if (!ft_strcmp(c, "OS"))
		close_shell("force quit");
	else if (!ft_strcmp(c, "[A"))
		printf("%s\n", history_before());
	else if (!ft_strcmp(c, "[B"))
		printf("%s\n", history_after());
	else if (!ft_strcmp(c, "[C"))
	{
		if (reader->pos < reader->size)
		{
			tputs(cursor_right, 1, ft_putchar);
			reader->pos++;
		}
	}
	else if (!ft_strcmp(c, "[D"))
	{
		if (reader->pos > 0)
		{
			tputs(cursor_left, 1, ft_putchar);
			reader->pos--;
		}
	}
	else
		g_shell.history_id = -1;
}

bool	process_key(char *c, t_reader *reader, char ***str)
{
	if (*c == '\n')
	{
		ft_putstr(c);
		return (false);
	}
	else if (*c == 127 && reader->pos > 0)
		unprint_char(str, reader);
	else if (*c == 27 && *(c + 1))
	{
		if (PRINT_TERMCAP)
			print_debug_termcap(c + 1);
		check_termcap(c + 1, reader);
	}
	else
		g_shell.history_id = -1;
	if (ft_isprint(*c))
		print_char(str, c, reader);
	return (true);
}

char	*get_str_rterm(char **str)
{
	char	*res;

	res = ft_strdup("");
	while (*str)
	{
		res = ft_strjoinf1(res, *str);
		str++;
	}
	return (res);
}
