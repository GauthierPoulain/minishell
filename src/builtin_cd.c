/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:47:54 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 14:02:26 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cd_err(int code, char *path)
{
	ft_putstr_fd(2, "cd: ");
	if (code == 1)
	{
		ft_putstr_fd(2, "no such file or directory: ");
		ft_putstr_fd(2, path);
	}
	else if (code == 2)
	{
		ft_putstr_fd(2, "not a directory: ");
		ft_putstr_fd(2, path);
	}
	ft_putstr_fd(2, "\n");
}

void	builtin_cd(char *path)
{
	int	ret;
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		cd_err(1, path);
		return ;
	}
	close(fd);
	fd = open(path, __O_DIRECTORY);
	if (fd == -1)
	{
		cd_err(2, path);
		return ;
	}
	close(fd);
	ret = chdir(path);
	if (ret == -1)
	{
		cd_err(1, path);
	}
	
}
