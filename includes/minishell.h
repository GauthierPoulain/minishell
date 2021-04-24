/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gapoulai <gapoulai@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:59:04 by gapoulai          #+#    #+#             */
/*   Updated: 2021/04/24 21:18:16 by gapoulai         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdarg.h>
# include <signal.h>

# define DEBUG 1

# define EXITMSG_NOPRINT	""
# define EXITMSG_HOW		"how ¿"
# define EXITMSG_MALLOC		"malloc error"
# define EXITMSG_GNL		"gnl error"
# define EXITMSG_SIGINT		"signal : SIGINT"
# define EXITMSG_UNEXPECTED	"unexpected error"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_minishell
{
	t_list	*gc;
}				t_minishell;

extern t_minishell	g_shell;

// LIB ------------------------------------------------------------------------

int		ft_gnl(int fd, char **line);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
t_list	*ft_lstnew(void *content);
void	ft_putstr_fd(int fd, char *str);
void	ft_putstr(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(char *s1);
char	*ft_strjoinc(char *s1, char c);
size_t	ft_strlen(char *str);
void	gc_clean(void);
void	gc_free(void *ptr);
void	*gc_malloc(size_t size);

// MINISHELL ------------------------------------------------------------------

void	close_shell(char *msg);
void	add_catchers(void);

#endif