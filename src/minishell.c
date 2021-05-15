#include "../includes/minishell.h"

t_minishell	g_shell;

void	reset_cio(void)
{
	g_shell.io.cin = 0;
	g_shell.io.cout = 1;
	g_shell.io.cerr = 2;
}

static void	init_shell(void)
{
	g_shell.gc = NULL;
	g_shell.workdir = gc_malloc(FILENAME_MAX);
	g_shell.last_return = 0;
	g_shell.env = NULL;
	g_shell.history.lst = NULL;
	ft_lstadd_front(&g_shell.history.lst, ft_lstnew(NULL));
	tcgetattr(STDIN_FILENO, &g_shell.save);
	g_shell.use_termcaps = false;
}

void	pre_prompt(void)
{
	if (get_env("USER") && get_env("HOME"))
	{
		ft_putcolor(get_env("USER"), _CYAN);
		ft_putcolor(" in ", _DARKGRAY);
		ft_putcolor(ft_strreplace(get_pwd(), get_env("HOME"), "~"), _CYAN);
		ft_putcolor("\n", _DARKGRAY);
	}
	if (g_shell.last_return == 0)
		ft_putcolor("›", _GREEN);
	else
	{
		ft_putcolor(ft_itoa(g_shell.last_return), _RED);
		ft_putcolor(" ›", _RED);
	}
	ft_putcolor(" ", _DARKGRAY);
}

int	main(int argc, const char **argv, const char **envp)
{
	(void)argc;
	init_shell();
	init_env(envp);
	set_env("SHELL", (char *)argv[0]);
	set_input_mode();
	add_signals_listeners();
	if (isatty(STDIN_FILENO))
	{
		while (true)
		{
			pre_prompt();
			g_shell.history.act_pos = 0;
			process_input(ft_strtrim_spaces(read_term()));
			reset_cio();
		}
	}
	else
		process_input(ft_strtrim_spaces(read_term()));
	close_shell(NULL);
}
