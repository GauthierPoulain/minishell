#include "../../includes/minishell.h"

char	**tab_add(char **argv, char *str)
{
	char	**res;
	char	**save;

	res = ft_calloc(sizeof(char *) * (ft_tab_len(argv) + 2));
	save = res;
	if (argv)
		while (*argv)
			*res++ = ft_strdup(*argv++);
	*res = ft_strdup(str);
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
	if (!actual->argv)
	{
		actual->operator = ft_strdup("noop");
		actual->argv = tab_add(actual->argv, "");
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
	while ((argv + i))
	{
		if (is_operator((argv + i)->str) && ft_strlen((argv + i)->str)
			== (size_t)is_operator((argv + i)->str))
		{
			check_operator(actual, argv, i);
			ft_lstadd_back(&lst, ft_lstnew(actual));
			actual = init_command_struct();
		}
		else
			actual->argv = tab_add(actual->argv, (argv + i)->str);
		i++;
	}
	if (actual->argv)
		ft_lstadd_back(&lst, ft_lstnew(actual));
	if (!check_struct(lst) || !fill_cmd_structs(lst))
		return (NULL);
	return (lst);
}
