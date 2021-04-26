/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:07:35 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 15:05:48 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_pwd(void)
{
	if (getcwd(g_shell.workdir, FILENAME_MAX) == NULL)
	{
		ft_putstr_fd(2, "error while getting current workdir\n");
		return (1);
	}
	ft_putstr(g_shell.workdir);
	ft_putstr("\n");
	return (0);
}
