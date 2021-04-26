/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:32:37 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 22:38:01 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	exec_test(void)
// {
// 	char	*prog = "/usr/bin/ls";
// 	char	*argv[] = {prog, NULL};
// 	char	*envp[] = {NULL};

// 	g_shell.last_return = exec_subprocess(prog, argv, envp);
// }

void	exec_test(void)
{
	set_env("SALUT", "bonjour");
	builtin_env();
	unset_env("SALUT");
	builtin_env();
	set_env("SALUT", "bonjour");
	set_env("USER", "gogoledozo");
}
