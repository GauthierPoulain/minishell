/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:44:12 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 19:50:55 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_err(int code)
{
	ft_putstr_fd(2, "Error:\n");
	if (code == 1)
		ft_putstr_fd(2, "Unexpexted Error\n");
	else if (code == 2)
		ft_putstr_fd(2, "Malloc error\n");
	else if (code == 2)
		ft_putstr_fd(3, "gnl failure\n");
}

void	close_shell(t_minishell *shell, int code)
{
	if (code)
		print_err(code);
	gc_clean(shell);
	if (code != 0)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}
