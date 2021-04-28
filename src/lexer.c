#include "../includes/minishell.h"

t_token	*get_token_info(char **line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '$')
		i++;
}

void	get_lexer(char *line)
{
	int		i;
	t_token	*token;

	i = 0;
	token = gc_malloc(sizeof(t_token));
	while (line[i])
	{

		i++;
	}
}