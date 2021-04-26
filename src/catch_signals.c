/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:56:07 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 18:25:53 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	catch_SIGINT(int sig)
{
	(void)sig;
	close_shell(NULL);
}

void	add_catchers(void)
{
	signal(SIGINT, catch_SIGINT);
}
