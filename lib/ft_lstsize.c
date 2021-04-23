/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 00:32:17 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 00:32:39 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_lstsize(t_list *lst)
{
	size_t	count;
	t_list	*next;

	count = 0;
	next = lst;
	while (next)
	{
		next = next->next;
		count++;
	}
	return (count);
}
