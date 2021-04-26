/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:58:41 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 15:39:45 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	g_shell;

static void	init_shell(void)
{
	g_shell.gc = NULL;
	g_shell.workdir = gc_malloc(FILENAME_MAX);
	g_shell.last_return = 0;
}

static void	pre_prompt(void)
{
	if (getcwd(g_shell.workdir, FILENAME_MAX) == NULL)
		close_shell("error while getting current workdir");
	ft_putcolor(g_shell.workdir, _BLUE);
	if (g_shell.last_return == 0)
		ft_putcolor(" > ", _GREEN);
	else
	{
		ft_putstr(" ");
		ft_putcolor(ft_itoa(g_shell.last_return), _RED);
		ft_putcolor(" > ", _RED);
	}
}

int	main(void)
{
	char	**line;
	int		gnl_ret;

	init_shell();
	line = gc_malloc(sizeof(char *));
	add_catchers();
	while (true)
	{
		pre_prompt();
		gnl_ret = ft_gnl(0, line);
		if (gnl_ret == -1)
			close_shell("gnl failure");
		else if (gnl_ret == 0 && ft_strlen(*line) == 0)
			close_shell(NULL);
		else
			process_input(*line);
		gc_free(*line);
	}
	close_shell("unexpecter error");
}
