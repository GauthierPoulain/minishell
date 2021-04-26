/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:37:34 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 19:22:54 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(sizeof(char) * (len + 1));
	if (s1)
		ft_memcpy(res, s1, ft_strlen(s1));
	if (s2)
		ft_strcat(res, (char *)s2);
	return (res);
}

char	*ft_strjoinf1(char *s1, char *s2)
{
	size_t	len;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(sizeof(char) * (len + 1));
	if (s1)
		ft_memcpy(res, s1, ft_strlen(s1));
	if (s2)
		ft_strcat(res, (char *)s2);
	gc_free(s1);
	return (res);
}

char	*ft_strjoinf2(char *s1, char *s2)
{
	size_t	len;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(sizeof(char) * (len + 1));
	if (s1)
		ft_memcpy(res, s1, ft_strlen(s1));
	if (s2)
		ft_strcat(res, (char *)s2);
	gc_free(s2);
	return (res);
}

char	*ft_strjoinall(char *s1, char *s2)
{
	size_t	len;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(sizeof(char) * (len + 1));
	if (s1)
		ft_memcpy(res, s1, ft_strlen(s1));
	if (s2)
		ft_strcat(res, (char *)s2);
	gc_free(s1);
	gc_free(s2);
	return (res);
}

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
	tlen = ft_strlen(s1) + 1;
	res = gc_malloc(sizeof(char) * (tlen + 1));
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = 0;
	gc_free(s1);
	return (res);
}
