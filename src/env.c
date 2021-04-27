/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:45:57 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/27 13:06:44 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_env(char *key, char *value)
{
	t_list	*actual;
	t_env	*content;

	actual = g_shell.env;
	while (actual)
	{
		content = actual->content;
		if (!ft_strcmp(key, content->key))
		{
			content->value = value;
			return ;
		}
		actual = actual->next;
	}
	content = gc_malloc(sizeof(t_env));
	content->key = key;
	content->value = value;
	ft_lstadd_back(&g_shell.env, ft_lstnew(content));
}

void	unset_env(char *key)
{
	t_list	*actual;
	t_env	*content;

	actual = g_shell.env;
	while (actual)
	{
		content = actual->content;
		if (!ft_strcmp(key, content->key) && content->value)
		{
			gc_free(content->value);
			content->value = NULL;
			return ;
		}
		actual = actual->next;
	}
}

char	*get_env(char *key)
{
	t_list	*actual;
	t_env	*content;

	actual = g_shell.env;
	while (actual)
	{
		content = actual->content;
		if (!ft_strcmp(key, content->key) && content->value)
			return (content->value);
		actual = actual->next;
	}
	return (NULL);
}

void	init_env(const char **envp)
{
	char	**env;
	char	**spres;

	env = (char **)envp;
	while (*env)
	{
		spres = ft_split(*env, '=');
		set_env(spres[0], *env + (ft_strlen(spres[0]) + 1));
		env++;
	}
}

char	**get_envp(void)
{
	char	**envp;
	t_list	*actual;
	t_env	*content;
	int		pos;

	envp = ft_calloc(sizeof(char *) * (ft_envlstsize(g_shell.env) + 1));
	pos = 0;
	actual = g_shell.env;
	while (actual)
	{
		content = actual->content;
		if (content && content->value)
			envp[pos++] = ft_strjoin(content->key, ft_strjoin("=",
						ft_strjoin(content->value, "\n")));
		actual = actual->next;
	}
	return (envp);
}
