/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:59:04 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 19:46:05 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdarg.h>

# define DEBUG 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_minishell
{
	t_list	*gc;
}				t_minishell;

// LIB ------------------------------------------------------------------------

int		ft_gnl(int fd, char **line, t_minishell *shell);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
t_list	*ft_lstnew(void *content, t_minishell *shell);
void	ft_putstr_fd(int fd, char *str);
void	ft_putstr(char *str);
char	*ft_strdup(char *s1, t_minishell *shell);
char	*ft_strjoinc(char *s1, char c, t_minishell *shell);
size_t	ft_strlen(char *str);
void	gc_clean(t_minishell *shell);
void	gc_free(void *ptr, t_minishell *shell);
void	*gc_malloc(size_t size, t_minishell *shell);

// MINISHELL ------------------------------------------------------------------

void	close_shell(t_minishell *shell, int code);

#endif