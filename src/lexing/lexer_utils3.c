#include "../../includes/minishell.h"

void	no_room_infos(char *line, int *i, t_infos *infos)
{
	while (line[*i] == '\\')
	{
		*i += 1;
		infos->len += 1;
	}
}
