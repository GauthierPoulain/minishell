/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 19:24:13 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 19:24:27 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	char	*rdest;

	rdest = dest;
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	return (rdest);
}
