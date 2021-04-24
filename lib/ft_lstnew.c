/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 00:31:36 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 20:19:15 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = gc_malloc(sizeof(t_list));
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
