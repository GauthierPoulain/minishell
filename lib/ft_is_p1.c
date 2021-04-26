/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_p1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 14:29:13 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 14:29:27 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_isalpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_isalnum(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

bool	ft_isascii(char c)
{
	return (c >= 0 && c <= 127);
}

bool	ft_isprint(char c)
{
	return (c >= 32 && c <= 126);
}
