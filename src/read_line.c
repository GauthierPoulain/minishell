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

void	reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_shell.save);
}

char	*read_term(void)
{
	char	*str;
	char	buff;
	int		len;
	int		ret;

	set_input_mode();
	len = 0;
	buff = 0;
	str = ft_strdup("");
	ret = 0;
	while (ret >= 0 && buff != '\n')
	{
		ret = read(STDIN_FILENO, &buff, 1);
		if (buff == 'q')
			close_shell(NULL);
		write(1, &buff, 1);
		len++;
		ft_strjoinc(str, buff);
	}
	reset_input_mode();
	return (str);
}
