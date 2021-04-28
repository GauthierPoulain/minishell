#include "../includes/minishell.h"

t_minishell	g_shell;

static void	init_shell(void)
{
	g_shell.gc = NULL;
	g_shell.workdir = gc_malloc(FILENAME_MAX);
	g_shell.last_return = 0;
	g_shell.env = NULL;
	tcgetattr(STDIN_FILENO, &g_shell.save);
}

static void	pre_prompt(void)
{
	ft_putcolor(get_env("USER"), _LIGHTBLUE);
	ft_putcolor(" in ", _DARKGRAY);
	ft_putcolor(ft_strreplace(get_pwd(), get_env("HOME"), "~"), _YELLOW);
	ft_putcolor("\n", _DARKGRAY);
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
	(void)argv;
	init_shell();
	init_env(envp);
	while (true)
	{
		pre_prompt();
		process_input(read_term());
	}
	close_shell("unexpecter error");
}
