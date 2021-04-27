#include "../includes/minishell.h"

size_t	ft_lstsize(t_list *alist)
{
	size_t	count;

	count = 0;
	while (alist)
	{
		count++;
		alist = alist->next;
	}
	return (count);
}

size_t	ft_envlstsize(t_list *alist)
{
	size_t	count;
	t_env	*content;

	count = 0;
	while (alist)
	{
		content = alist->content;
		if (content->value)
			count++;
		alist = alist->next;
	}
	return (count);
}
