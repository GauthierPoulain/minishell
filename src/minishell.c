/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:58:41 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 21:28:30 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	g_shell;

void	init_shell(void)
{
	g_shell.gc = NULL;
}

void	process_input(char *line)
{
	if (!ft_strcmp(line, "exit"))
	{
		close_shell(EXITMSG_NOPRINT);
	}
}

int	main(void)
{
	char	**line;

	init_shell();
	line = gc_malloc(sizeof(char *));
	add_catchers();
	while (true)
	{
		ft_putstr("$ ");
		if (ft_gnl(0, line) == -1)
			close_shell(EXITMSG_GNL);
		process_input(*line);
		gc_free(*line);
	}
	close_shell(EXITMSG_UNEXPECTED);
}
