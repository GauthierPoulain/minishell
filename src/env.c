/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:45:57 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/26 22:38:10 by gapoulai         ###   ########lyon.fr   */
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
