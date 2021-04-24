/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:37:34 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 21:04:05 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoinc(char *s1, char c)
{
	int		i;
	int		tlen;
	char	*res;

	i = 0;
	if (!s1)
	{
		res = gc_malloc(sizeof(char) * 2);
		res[0] = c;
		res[1] = 0;
		return (res);
	}
	tlen = ft_strlen(s1) + 2;
	res = gc_malloc(sizeof(char) * tlen);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	gc_free(s1);
	res[i] = c;
	res[i + 1] = 0;
	return (res);
}
