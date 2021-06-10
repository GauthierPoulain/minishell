#include "../../includes/minishell.h"

size_t	ft_toktab_len(t_ptoken *car)
{
	size_t	res;

	res = 0;
	while (car && car->str)
	{
		car++;
		res++;
	}
	return (res);
}

static t_ptoken	*tab_add(t_ptoken *argv, t_ptoken str)
{
	t_ptoken	*res;
	t_ptoken	*save;

	printf("tab len = %zu\n", ft_toktab_len(argv) + 2);
	res = ft_calloc(sizeof(t_ptoken) * (ft_toktab_len(argv) + 2));
	save = res;
	while (argv && argv->str)
	{
		// *res++ = *argv++;
		res->is_escaped = argv->is_escaped;
		res->squotes = argv->squotes;
		res->str = ft_strdup(argv->str);
		printf("ahhh %s\n", argv->str);
		res++;
		argv++;
	}
	res->is_escaped = str.is_escaped;
	res->squotes = str.squotes;
	res->str = ft_strdup(str.str);
	// *res = *str;
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
	return (cmd);
}

bool	check_struct(t_list	*lst)
{
	t_command	*cmd;

	while (lst)
	{
		cmd = lst->content;
		if (cmd->operator && ft_strcmp(cmd->operator, ";") && !lst->next)
			return (false);
		lst = lst->next;
	}
	return (true);
}

void	check_operator(t_command *actual, t_ptoken *argv, int i)
{
	t_ptoken	tmp;

	if (!actual->token)
	{
		actual->operator = ft_strdup("noop");
		tmp.is_escaped = false;
		tmp.squotes = false;
		tmp.str = ft_strdup("");
		actual->token = tab_add(actual->token, tmp);
	}
	else
		actual->operator = ft_strdup((argv + i)->str);
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
	{
		printf("is escaped [%s] ? %d\n", (argv +i)->str ,(argv + i)->is_escaped);
		if (is_operator((argv + i)->str) && ft_strlen((argv + i)->str)
			== (size_t)is_operator((argv + i)->str) && !(argv + i)->is_escaped)
		{
			check_operator(actual, argv, i);
			ft_lstadd_back(&lst, ft_lstnew(actual));
			actual = init_command_struct();
		}
		else if (!ft_strcmp("\"", (argv + i)->str) || !ft_strcmp("\'", (argv + i)->str))
		{
			if ((argv + i)->is_escaped)
				actual->token = tab_add(actual->token, *(argv + i));
		}
		else
	{
		actual->token = tab_add(actual->token, *(argv + i));
	}	
		i++;
	}
	if (actual->token)
		ft_lstadd_back(&lst, ft_lstnew(actual));
	if (!check_struct(lst) || !fill_cmd_structs(lst))
		return (NULL);
	return (lst);
}
