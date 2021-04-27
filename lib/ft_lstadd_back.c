#include "../includes/minishell.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = *alst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
