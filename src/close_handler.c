/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:44:12 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 21:22:54 by gapoulai         ###   ########lyon.fr   */
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
	if (DEBUG && ft_strlen(msg) > 0)
		print_err(msg);
	exit(EXIT_SUCCESS);
}
