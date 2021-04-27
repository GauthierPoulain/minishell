#include "../includes/minishell.h"

void	gc_free(void *ptr)
{
	t_list	*gc;
	bool	nxt;

	gc = g_shell.gc;
	nxt = true;
	while (gc && nxt)
	{
		if (gc->content == ptr)
		{
			free(ptr);
			gc->content = NULL;
			nxt = false;
		}
		gc = gc->next;
	}
}
