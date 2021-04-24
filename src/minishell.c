/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:58:41 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 14:24:20 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(t_minishell *shell)
{
	shell->gc = NULL;
}

void	close_shell(t_minishell *shell, int code)
{
	gc_clean(&shell->gc);
	if (code != 0)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

int	main(void)
{
	t_minishell	shell;

	init_shell(&shell);
	close_shell(&shell, 0);
}
