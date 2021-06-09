#include "../../includes/minishell.h"

typedef struct s_splitter
{
	bool	in_quotes;
	bool	in_dquotes;
}				t_splitter;

static bool	check_char(t_splitter *splitter, char *c, int *i)
{
	if (*c == '\\')
	{
		if (*(c + 1))
			*i += 1;
		else
			return (false);
	}
	else if (*c == '\"' && !splitter->in_quotes)
		splitter->in_dquotes = !splitter->in_dquotes;
	else if (*c == '\'' && !splitter->in_dquotes)
		splitter->in_quotes = !splitter->in_quotes;
	return (true);
}

static void	init_this(t_splitter *splitter)
{
	splitter->in_dquotes = false;
	splitter->in_quotes = false;
}

t_list	*split_commands(char *line)
{
	t_splitter	splitter;
	t_list		*cmds;
	int			i;
	int			op_check;
	char		*tmp;

	cmds = NULL;
	tmp = NULL;
	init_this(&splitter);
	i = 0;
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
