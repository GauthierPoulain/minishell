/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 00:44:40 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 18:41:02 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(char *s1, t_minishell *shell)
{
	char	*str;
	int		len;
	int		i;

	len = ft_strlen(s1);
	str = gc_malloc(sizeof(char) * (len + 1), shell);
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
