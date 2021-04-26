/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:33:54 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 14:41:43 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_itoa(int n)
{
	char		*res;
	int			count;
	int			i;
	long int	tmp;

	tmp = n;
	count = ft_nblen(n);
	if (tmp < 0 || count == 0)
		count++;
	res = gc_malloc(sizeof(char) * (count + 1));
	ft_bzero(res, count + 1);
	i = 0;
	if (tmp < 0)
	{
		tmp *= -1;
		res[i++] = '-';
	}
	while (count > i)
	{
		res[--count] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (res);
}
