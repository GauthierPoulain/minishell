/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:58:41 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/27 15:24:42 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

// static void	set_raw_input(void)
// {
// 	printf("salut");
// 	tcgetattr(STDIN_FILENO, &g_shell.termios_ctl);
// 	g_shell.termios_ctl = g_shell.termios_ctl;
// 	g_shell.termios_ctl.c_cflag &= ~(ECHO | ICANON);
// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_shell.termios_ctl);
// }

int	main(int argc, const char **argv, const char **envp)
{
	char	**line;
	int		gnl_ret;

	(void)argc;
	(void)argv;
	init_shell();
	// set_raw_input();
	init_env(envp);
	line = gc_malloc(sizeof(char *));
	add_catchers();
	while (true)
	{
		pre_prompt();
		gnl_ret = ft_gnl(STDIN_FILENO, line);
		if (gnl_ret == -1)
			close_shell("gnl failure");
		else if (gnl_ret == 0 && ft_strlen(*line) == 0)
			close_shell(NULL);
		else
			process_input(*line);
		if (*line)
			gc_free(*line);
	}
	close_shell("unexpecter error");
}
