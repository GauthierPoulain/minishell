#include "../includes/minishell.h"

t_minishell	g_shell;

static void	init_shell(void)
{
	g_shell.gc = NULL;
	g_shell.workdir = gc_malloc(FILENAME_MAX);
	g_shell.last_return = 0;
	g_shell.env = NULL;
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
	setbuf(stdout, NULL);
}

static void	pre_prompt(void)
{
	ft_putcolor(get_env("USER"), _LIGHTBLUE);
	ft_putcolor(" in ", _DARKGRAY);
	ft_putcolor(get_env("PWD"), _YELLOW);
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
	char	**line;

	(void)argc;
	(void)argv;
	init_shell();
	init_env(envp);
	line = gc_malloc(sizeof(char *));
	while (true)
	{
		pre_prompt();		
		process_input(read_term());
	}
	close_shell("unexpecter error");
}
