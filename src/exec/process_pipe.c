#include "../../includes/minishell.h"

void	process_pipe(char *buffer)
{
	print_debug_termcap(buffer);
	cut_eof(buffer);
	ft_putcolor(buffer, _BLUE);
	ft_bzero(buffer, GNL_BUFFER_SIZE + 1);
}