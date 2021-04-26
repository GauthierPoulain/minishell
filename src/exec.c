/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 22:18:41 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 22:19:01 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_subprocess(char *path, char *argv[], char *envp[])
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		close_shell("error while forking subprocess");
	else if (pid == 0)
	{
		execve(path, argv, envp);
		gc_clean();
		exit(errno);
	}
	else
		wait(&status);
	return (((status) & 0xff00) >> 8);
}
