#include "../includes/minishell.h"

char	*parse_line(char **line)
{
	int			i;
	char		*env_value;
	t_parser	parser;

	i = 0;
	parser.s_quotes = -1;
	parser.quotes = -1;
	parser.new_line = *line;
	while (parser.new_line[i])
	{
		if (parser.new_line[i] == 47)		// ascii for [']
		{
			parser.s_quotes = !parser.s_quotes;
		}
		if (parser.new_line[i] == '$')
		{
			if (parser.new_line[i + 1] == '?')
				env_value = ft_itoa(g_shell.last_return);
			else
				env_value = get_env(get_word_sp(parser.new_line, i + 1));
			if (!env_value)
				break ;
			parser.new_line = set_env_line(parser.new_line, env_value, i);
		}
		i++;
	}
	*line = parser.new_line;
	return (*line);
}