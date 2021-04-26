/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:12:12 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 14:05:04 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	preexec(char *cmd)
{
	(void)cmd;
	return ;
}

static void	precmd()
{
	return ;
}

void	process_input(char *line)
{
	preexec(line);
	if (!ft_strcmp(line, "exit"))
		close_shell(NULL);
	else if (!ft_strcmp(line, "ls"))
		exec_test();
	else if (!ft_strcmp(line, "cd"))
		builtin_cd("/usr");
	precmd();
}