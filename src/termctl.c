#include "../includes/minishell.h"

void	set_input_mode(void)
{
	char	*term_name;

	term_name = get_env("TERM");
	if (isatty(STDIN_FILENO) && term_name
		&& tgetent(g_shell.termbuffer, term_name) > 0)
	{
		tcgetattr(STDIN_FILENO, &g_shell.term);
		g_shell.term.c_lflag &= ~(ICANON | ECHO);
		g_shell.term.c_cc[VMIN] = 1;
		g_shell.term.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &g_shell.term);
		g_shell.use_termcaps = true;
	}
	else
		if (DEBUG)
			ft_putstr("termcaps disabled\n");
}

void	reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_shell.save);
	g_shell.use_termcaps = false;
}

void	cursor_op(char *op)
{
	ft_putstr(op);
}
