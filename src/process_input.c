/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:12:12 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 15:19:52 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	preexec(char *cmd)
{
	(void)cmd;
	return ;
}

static void	precmd(void)
{
	return ;
}

void	process_input(char *line)
{
	preexec(line);
	if (ft_strlen(line) < 1)
		return ;
	if (!ft_strcmp(line, "exit"))
		close_shell(NULL);
	else if (!ft_strcmp(line, "test"))
		exec_test();
	else if (!ft_strcmp(line, "cd"))
		g_shell.last_return = builtin_cd("/ergerzgerzg");
	else if (!ft_strcmp(line, "pwd"))
		g_shell.last_return = builtin_pwd();
	else
	{
		ft_putstr_fd(2, "minishell: command not found: ");
		ft_putstr_fd(2, line);
		ft_putstr_fd(2, "\n");
		g_shell.last_return = 127;
	}
	precmd();
}
