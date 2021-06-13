#include "../../includes/minishell.h"

t_ptoken	*toktab_add(t_ptoken *argv, t_ptoken str)
{
	t_ptoken	*res;
	t_ptoken	*save;

	res = ft_calloc(sizeof(t_ptoken) * (ft_toktab_len(argv) + 2));
	save = res;
	while (argv && argv->str)
	{
		res->is_escaped = argv->is_escaped;
		res->is_in_squotes = argv->is_in_squotes;
		res->is_in_quotes = argv->is_in_quotes;
		res->spaces = argv->spaces;
		res->escapes = argv->escapes;
		res->spaces_after = argv->spaces_after;
		res->skip_join = argv->skip_join;
		res->str = ft_strdup(argv->str);
		res++;
		argv++;
	}
	toktab_add_p2(res, str);
	return (save);
}

t_command	*init_command_struct(void)
{
	t_command	*cmd;

	cmd = gc_malloc(sizeof(t_command));
	cmd->operator = NULL;
	cmd->listen_stdout = true;
	cmd->listen_stderr = false;
	cmd->need_pipe = false;
	cmd->need_redirect = false;
	cmd->path = NULL;
	cmd->prog = NULL;
	cmd->redirect_append = false;
	cmd->redirect_path = NULL;
	cmd->argv = NULL;
	cmd->skip_exec = false;
	cmd->file_input = false;
	cmd->token = NULL;
	cmd->qcheck.d = false;
	cmd->qcheck.s = false;
	return (cmd);
}

void	check_operator(t_command *actual, t_ptoken *argv, int i)
{
	t_ptoken	tmp;

	if (!actual->token)
	{
		actual->operator = ft_strdup("noop");
		tmp.is_escaped = false;
		tmp.escapes = 0;
		tmp.is_in_squotes = false;
		tmp.is_in_quotes = false;
		tmp.spaces = 0;
		tmp.spaces_after = 0;
		tmp.skip_join = false;
		tmp.str = ft_strdup("");
		actual->token = toktab_add(actual->token, tmp);
	}
	else
		actual->operator = ft_strdup((argv + i)->str);
}

static void	loop(t_command **actual, t_ptoken *argv, int *i, t_list **lst)
{
	if (is_operator((argv + *i)->str) && ft_strlen((argv + *i)->str)
		== (size_t)is_operator((argv + *i)->str) && !(argv + *i)->is_escaped
		&& !(argv + *i)->is_in_quotes && !(argv + *i)->is_in_squotes)
		check_op_omg(actual, argv, i, lst);
	else if (!ft_strcmp("\"", (argv + *i)->str) || !ft_strcmp("\'",
			(argv + *i)->str))
	{
		if ((argv + *i)->is_escaped)
			(*actual)->token = toktab_add((*actual)->token, *(argv + *i));
		else
			super_check_quotes(actual, argv, i);
	}
	else
		(*actual)->token = toktab_add((*actual)->token, *(argv + *i));
	*i += 1;
}

t_list	*get_commands(t_ptoken *argv)
{
	t_list		*lst;
	t_command	*actual;
	int			i;

	lst = NULL;
	i = 0;
	actual = init_command_struct();
	while ((argv + i)->str)
		loop(&actual, argv, &i, &lst);
	if (actual->token)
		ft_lstadd_back(&lst, ft_lstnew(actual));
	if (!check_struct(lst))
		return (NULL);
	return (lst);
}
