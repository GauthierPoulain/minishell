/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:44:12 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 13:37:08 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_err(char *msg)
{
	ft_putstr_fd(2, "exit: ");
	ft_putstr_fd(2, msg);
	ft_putstr_fd(2, "\n");
}

void	close_shell(char *msg)
{
	gc_clean();
	if (msg)
	{
		if (DEBUG)
			print_err(msg);
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);
}
