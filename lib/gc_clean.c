/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:47:42 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 20:56:38 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	gc_clean(void)
{
	t_list	*gc;
	t_list	*tmp;

	gc = g_shell.gc;
	while (gc)
	{
		tmp = gc->next;
		if (gc->content)
			free(gc->content);
		free(gc);
		gc = tmp;
	}
}
