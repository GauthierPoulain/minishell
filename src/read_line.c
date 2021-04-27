#include "../includes/minishell.h"

char	*read_term(void)
{
	char	*str;
	char	*buff;
	int		len;

	len = 0;
	buff = NULL;
	str = ft_strdup("");
	tcgetattr(0, &g_shell.term);
	tcgetattr(0, &g_shell.save);
	g_shell.term.c_cflag &= ~(ECHO);
	g_shell.term.c_cflag &= ~(ICANON);
	g_shell.term.c_cflag &= ~(ISIG);
	g_shell.term.c_cc[VMIN] = 1;
	g_shell.term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_shell.term);
	tgetent(0, getenv("TERM"));
	while (read(0, buff, 1) >= 0 && *buff != '\n')
	{
		write(1, buff, 1);
		if (*buff == 'c')
			write(1, "salut", 5);
		len++;
		ft_strjoinc(str, *buff);
	}
	tcsetattr(0, TCSANOW, &g_shell.save);
	return (str);
}
