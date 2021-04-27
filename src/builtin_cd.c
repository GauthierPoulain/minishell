/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 13:47:54 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/27 12:22:19 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cd_err(int code, char *path)
{
	if (code == 0)
		return (0);
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
	return (1);
}

int	builtin_cd(char *path)
{
	int	ret;
	int	fd;
	int	err_code;

	err_code = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		err_code = 1;
	else
		close(fd);
	fd = open(path, O_DIRECTORY);
	if (fd == -1)
		err_code = 2;
	else
		close(fd);
	if (err_code == 0)
	{
		ret = chdir(path);
		if (ret == -1)
			cd_err(1, path);
		else
			set_env("PWD", path);
	}	
	return (cd_err(err_code, path));
}
