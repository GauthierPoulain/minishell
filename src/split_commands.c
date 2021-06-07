#include "../includes/minishell.h"

typedef struct s_splitter
{
	bool	in_quotes;
	bool	in_dquotes;
	bool	is_escaped;
}				t_splitter;

static bool	check_char(t_splitter *splitter, char *c, int *i)
{
	if (*c == '\\')
	{
		splitter->is_escaped = true;
		if (*(c + 1))
			*i += 1;
		else 
			return (false);
	}
	else if (*c == '\"' && !splitter->is_escaped && !splitter->in_quotes)
		splitter->in_dquotes = !splitter->in_dquotes;
	else if (*c == '\'' && !splitter->is_escaped && !splitter->in_dquotes)
		splitter->in_quotes = !splitter->in_quotes;
	return (true);
}

t_list	*split_commands(char *line)
{
	t_splitter	splitter;
	t_list		*cmds;
	int			i;
	int			op_check;
	char		*tmp;

	cmds = NULL;
	i = 0;
	splitter.in_dquotes = false;
	splitter.in_quotes = false;
	splitter.is_escaped = false;
	tmp = NULL;
	while (line[i])
	{
		tmp = ft_strjoinc(tmp, line[i]);
		if (!check_char(&splitter, line + i, &i))
			return (NULL);
		op_check = is_operator(line + i);
		if (op_check != 0)
		{
			ft_lstadd_back(&cmds, ft_lstnew(ft_strdup(tmp)));
			tmp = NULL;
		}
		i++;
	}
	ft_lstadd_back(&cmds, ft_lstnew(ft_strdup(tmp)));
	return (cmds);
}
