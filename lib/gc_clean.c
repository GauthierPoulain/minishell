/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:47:42 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 14:22:58 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	gc_clean(t_list **gc)
{
	t_list	*tmp;

	while (*gc)
	{
		tmp = (*gc)->next;
		if ((*gc)->content)
			free((*gc)->content);
		free(*gc);
		*gc = tmp;
	}
}
