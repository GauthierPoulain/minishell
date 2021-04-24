/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:04:46 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 13:22:53 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*gc_malloc(size_t size, t_minishell *shell)
{
	void	*alloc;
	t_list	*lst;

	alloc = malloc(size);
	lst = malloc(sizeof(t_list));
	if (!alloc || !lst)
		close_shell(shell, 1);
	lst->content = alloc;
	lst->next = NULL;
	ft_lstadd_front(&shell->gc, lst);
	return (alloc);
}
