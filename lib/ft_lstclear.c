#include "../includes/minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (*lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			gc_free((*lst)->content);
			gc_free(*lst);
			*lst = temp;
		}
	}
}