/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:32:37 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 13:39:50 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_subprocess(char *path, char *argv[], char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		close_shell("error while forking subprocess");
	if (pid == 0)
		execve(path, argv, envp);
	else
		wait(NULL);
}

void	exec_test()
{
	char	*argv[] = {"", NULL};
	char	*envp[] = {NULL};
	char	*prog	= "/usr/bin/ls";

	exec_subprocess(prog, argv, envp);
}
