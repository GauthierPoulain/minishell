/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:56:07 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 21:11:28 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	catch_SIGINT(int sig)
{
	(void)sig;
	close_shell(EXITMSG_SIGINT);
}

void	add_catchers(void)
{
	signal(SIGINT, catch_SIGINT);
}
