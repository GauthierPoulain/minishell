/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:58:41 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 19:53:49 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(t_minishell *shell)
{
	shell->gc = NULL;
}

int	main(void)
{
	t_minishell	shell;
	char		**line;

	line = NULL;
	line = gc_malloc(sizeof(char *), &shell);
	init_shell(&shell);
	while (true)
	{
		ft_putstr("$");
		if (ft_gnl(0, line, &shell) == -1)
			close_shell(&shell, 3);
		ft_putstr("line = ");
		ft_putstr(*line);
	}
	close_shell(&shell, 1);
}
