/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:52:05 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 19:41:00 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_first(t_minishell *shell, bool *nxt)
{
	t_list	*gc;
	t_list	*tmp;

	gc = shell->gc;
	tmp = gc->next;
	free(gc->content);
	free(gc);
	shell->gc = tmp;
	*nxt = false;
}

void	gc_free(void *ptr, t_minishell *shell)
{
	t_list	*gc;
	t_list	*actual;
	t_list	*tmp;
	bool	nxt;

	gc = shell->gc;
	nxt = true;
	if (gc && gc->content == ptr)
		free_first(shell, &nxt);
	while (gc && nxt)
	{
		if (gc->next && gc->next->content == ptr)
		{
			actual = gc->next;
			tmp = actual->next;
			free(actual->content);
			free(actual);
			gc->next = tmp;
			nxt = false;
		}
		gc = gc->next;
	}
}
