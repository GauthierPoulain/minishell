/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 00:31:36 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 18:40:58 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_lstnew(void *content, t_minishell *shell)
{
	t_list	*lst;

	lst = gc_malloc(sizeof(t_list), shell);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
