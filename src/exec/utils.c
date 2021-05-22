#include "../../includes/minishell.h"

void	cut_eof(char *str)
{
	char	*pos;

	pos = ft_strchr(str, EOF);
	if (pos)
		*pos = 0;
}
