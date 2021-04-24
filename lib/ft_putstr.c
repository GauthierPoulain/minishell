/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 18:45:34 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 18:46:53 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

void	ft_putstr(char *str)
{
	ft_putstr_fd(1, str);
}
