#include "../../includes/minishell.h"

static void	get_redirect_path(t_list *cmd)
{
	t_command	*actual;
	t_command	*next;
	int			i;

	actual = cmd->content;
	next = cmd->next->content;
	actual->redirect_path = next->argv[0];
	i = 1;
	while (next->argv[i])
	{
		actual->additional_content = ft_strjoinf1(actual->additional_content,
				next->argv[i]);
		i++;
	}
}

static void	parse_operators2(t_command *cmd, t_list *lst)
{
	if (!ft_strcmp(cmd->operator, ">"))
	{
		((t_command *)lst->next->content)->skip_exec = true;
		cmd->need_redirect = true;
		get_redirect_path(lst);
	}
	else if (!ft_strcmp(cmd->operator, ">>"))
	{
		((t_command *)lst->next->content)->skip_exec = true;
		cmd->need_redirect = true;
		cmd->redirect_append = true;
		get_redirect_path(lst);
	}
	else if (!ft_strcmp(cmd->operator, "<"))
	{
		((t_command *)lst->next->content)->skip_exec = true;
		cmd->file_input = true;
		get_redirect_path(lst);
	}
}

void	fill_cmd_structs(t_list *lst)
{
	t_command	*cmd;

	while (lst)
	{
		cmd = lst->content;
		printf("next = %p\n", lst->next);
		printf("salut\n");
		cmd->prog = cmd->argv[0];
		cmd->path = which(cmd->prog);
		if (!cmd->operator)
			;
		if (!ft_strcmp(cmd->operator, ";"))
		{
		}
		else if (!ft_strcmp(cmd->operator, "|"))
		{
			cmd->need_pipe = true;
		}
		else
			parse_operators2(cmd, lst);
		lst = lst->next;
	}
}
