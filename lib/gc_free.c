/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:01:11 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 21:13:23 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	gc_free(void *ptr)
{
	t_list	*gc;
	bool	nxt;

	gc = g_shell.gc;
	nxt = true;
	while (gc && nxt)
	{
		if (gc->content == ptr)
		{
			free(ptr);
			gc->content = NULL;
			nxt = false;
		}
		gc = gc->next;
	}
}
