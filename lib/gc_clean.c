/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:47:42 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 19:11:11 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	gc_clean(t_minishell *shell)
{
	t_list	*gc;
	t_list	*tmp;

	gc = shell->gc;
	while (gc)
	{
		tmp = gc->next;
		if (gc->content)
			gc_free(gc->content, shell);
		gc_free(gc, shell);
		gc = tmp;
	}
}
