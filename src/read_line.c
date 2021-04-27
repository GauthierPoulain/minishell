#include "../includes/minishell.h"
#define KEY_BUFFER_SIZE	4096

void	set_input_mode(void)
{
	char	*term_name;

	if (!isatty(STDIN_FILENO))
		close_shell("error, not a terminal");
	term_name = get_env("TERM");
	if (!term_name)
		close_shell("invalid terminal name (check env var)");
	if (tgetent(NULL, term_name) < 1)
		close_shell("error with termcap database");
	tcgetattr(STDIN_FILENO, &g_shell.term);
	g_shell.term.c_lflag &= ~(ICANON | ECHO | ISIG);
	g_shell.term.c_cc[VMIN] = 1;
	g_shell.term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_shell.term);
}

void	reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_shell.save);
}

void	add_char(char **str, char *c, t_reader *reader)
{
	if (reader->pos < reader->size)
	{
		;
	}
	else
	{
		ft_putstr(c);
		*str = ft_strjoin(*str, c);
		reader->size++;
		reader->pos++;
	}
}

void	check_termcap(char *c, t_reader *reader)
{
	if (!*c)
		;
	else if (!ft_strcmp(c, "[A"))
		; // up arrow
	else if (!ft_strcmp(c, "[B"))
		; // down arrow
	else if (!ft_strcmp(c, "[C"))
	{
		// right arrow
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
		//left arrow
	}
}

void	print_debug_termcap(char *c)
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

char	*delete_char(char *str, int pos)
{
	char	*res;
	int		i;

	res = ft_calloc(sizeof(char) * (ft_strlen(str)));
	i = 0;
	while (str[i] && i < pos)
	{
		res[i] = str[i];
		i++;
	}
	i++;
	while (str[i])
	{
		res [i - 1] = str[i];
		i++;
	}
	gc_free(str);
	return (res);
}

char	*addchar(char *str, char c, int pos)
{
	char	*res;
	int		i;

	res = ft_calloc(sizeof(char) * (ft_strlen(str) + 2));
	i = 0;
	while (str[i] && i < pos)
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = c;
	while (str[i - 1])
	{
		res[i] = str[i - 1];
		i++;
	}
	gc_free(str);
	return (res);
}

bool	process_key(char *c, t_reader *reader, char **str)
{
	// print_debug_termcap(c);
	if (*c == '-')
		close_shell("force quit");
	if (*c == '\n')
	{
		ft_putstr(c);
		return (false);
	}
	else if (*c == 127)
		*str = delete_char(*str, reader->pos);
	else if (*c == 27)
		check_termcap(c + 1, reader);
	else if(ft_isprint(*c))
		add_char(str, c, reader);
	return (true);
}

char	*read_term(void)
{
	char		*str;
	char		buffer[KEY_BUFFER_SIZE + 1];
	bool		reading;
	t_reader	reader;

	reader.size = 0;
	reader.pos = 0;
	reading = true;
	str = ft_strdup("");
	set_input_mode();
	ft_bzero(buffer, KEY_BUFFER_SIZE + 1);
	while (reading && read(STDIN_FILENO, buffer, KEY_BUFFER_SIZE) >= 0)
	{
		reader.print = true;
		reading = process_key(buffer, &reader, &str);
		ft_bzero(buffer, KEY_BUFFER_SIZE);
	}
	return (str);
}
