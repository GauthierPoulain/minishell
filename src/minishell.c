/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:58:41 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/25 02:17:14 by gapoulai         ###   ########lyon.fr   */
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

void	pre_prompt(void)
{
	ft_putcolor("minishell", _BLUE);
	ft_putcolor(" >> ", _GREEN);
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
			close_shell(EXITMSG_GNL);
		else if (gnl_ret == 0 && ft_strlen(*line) == 0)
			close_shell(EXITMSG_NOPRINT);
		else
			process_input(*line);
		gc_free(*line);
	}
	close_shell(EXITMSG_UNEXPECTED);
}
