/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:04:46 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 13:38:47 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*gc_malloc(size_t size)
{
	void	*alloc;
	t_list	*lst;

	alloc = malloc(size);
	lst = malloc(sizeof(t_list));
	if (!alloc || !lst)
		close_shell("malloc failure");
	lst->content = alloc;
	lst->next = NULL;
	ft_lstadd_front(&g_shell.gc, lst);
	return (alloc);
}
