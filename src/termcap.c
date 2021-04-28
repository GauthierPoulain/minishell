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

static void	check_termcap(char *c, t_reader *reader)
{
	if (PRINT_TERMCAP)
		print_debug_termcap(c);
	if (!*c)
		;
	else if (!ft_strcmp(c, "[A"))
		; // up arrow
	else if (!ft_strcmp(c, "[B"))
		; // down arrow
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
}

bool	process_key(char *c, t_reader *reader, char **str)
{
	if (*c == '-')
		close_shell("force quit");
	if (*c == '\n')
	{
		ft_putstr(c);
		return (false);
	}
	else if (*c == 127 && reader->pos > 0)
		unprint_char(str, reader);
	else if (*c == 27)
		check_termcap(c + 1, reader);
	else if (ft_isprint(*c))
		print_char(str, c, reader);
	return (true);
}
