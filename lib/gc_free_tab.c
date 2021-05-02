#include "../includes/minishell.h"

void	gc_free_tab(char **arr)
{
	while (*arr)
		gc_free(*arr++);
	gc_free(arr);
}
