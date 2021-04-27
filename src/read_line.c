#include "../includes/minishell.h"

void	set_input_mode(void)
{
	if (!isatty(STDIN_FILENO))
		close_shell("error, not a terminal");
	tcgetattr(STDIN_FILENO, &g_shell.save);
	tcgetattr(STDIN_FILENO, &g_shell.term);
	g_shell.term.c_lflag &= ~(ICANON | ECHO | ISIG);
	g_shell.term.c_cc[VMIN] = 1;
	g_shell.term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_shell.term);
}

void	process_key(char c, int *len, char **str)
{
	write(1, &c, 1);
	if (c == 'q')
		close_shell(NULL);
	(void)*len++;
	*str = ft_strjoinc(*str, c);
}

char	*read_term(void)
{
	char	*str;
	char	buff;
	int		len;

	len = 0;
	buff = 0;
	str = ft_strdup("");
	while (read(STDIN_FILENO, &buff, 1) >= 0 && buff != '\n')
		process_key(buff, &len, &str);
	return (str);
}
