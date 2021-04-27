#include "../includes/minishell.h"

void	*gc_malloc(size_t size)
{
	void	*alloc;
	t_list	*lst;

	alloc = malloc(size);
	lst = malloc(sizeof(t_list));
	if (!alloc || !lst)
		close_shell("malloc failure");
	lst->content = alloc;
	lst->next = NULL;
	ft_lstadd_front(&g_shell.gc, lst);
	return (alloc);
}
