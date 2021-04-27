#include "../includes/minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = gc_malloc(sizeof(t_list));
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
