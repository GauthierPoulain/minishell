#include "../includes/minishell.h"

void	gc_clean(void)
{
	t_list	*gc;
	t_list	*tmp;

	gc = g_shell.gc;
	while (gc)
	{
		tmp = gc->next;
		if (gc->content)
			free(gc->content);
		free(gc);
		gc = tmp;
	}
}
