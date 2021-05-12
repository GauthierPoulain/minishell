#include "../includes/minishell.h"

void	set_input_mode(void)
{
	char	*term_name;

	if (!isatty(STDIN_FILENO))
		close_shell("error, not a terminal");
	term_name = get_env("TERM");
	if (!term_name)
		close_shell("invalid terminal name (check env var)");
	if (tgetent(g_shell.termbuffer, term_name) < 1)
		close_shell("error with termcap database");
	tcgetattr(STDIN_FILENO, &g_shell.term);
	g_shell.term.c_lflag &= ~(ICANON | ECHO);
	g_shell.term.c_cc[VMIN] = 1;
	g_shell.term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_shell.term);
}

void	reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_shell.save);
}
