/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:32:37 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/27 12:46:56 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_test(void)
{
	char	*prog = "/bin/ls";
	char	*argv[] = {prog, "/bin", NULL};

	sleep(2);
	g_shell.last_return = exec_subprocess(prog, argv);
}

// void	exec_test(void)
// {
// 	char	**envp;

// 	envp = get_envp();
// 	while (*envp)
// 	{
// 		ft_putstr(*envp);
// 		envp++;
// 	}
// }
