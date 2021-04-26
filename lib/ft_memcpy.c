/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 19:23:28 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 19:23:46 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*castd;
	const char	*casts;

	if (!dst && !src)
		return (NULL);
	castd = dst;
	casts = src;
	while (n--)
		*castd++ = *casts++;
	return (dst);
}
