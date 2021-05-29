#include "../../includes/minishell.h"

static void	parse_operators2(t_command *cmd, t_list *lst)
{
	if (!ft_strcmp(cmd->operator, ">"))
	{
		((t_command *)lst->next->content)->skip_exec = true;
		cmd->need_redirect = true;
		cmd->redirect_path = ((t_command *)lst->next->content)->argv[0];
	}
	else if (!ft_strcmp(cmd->operator, ">>"))
	{
		((t_command *)lst->next->content)->skip_exec = true;
		cmd->need_redirect = true;
		cmd->redirect_append = true;
		cmd->redirect_path = ((t_command *)lst->next->content)->argv[0];
	}
	else if (!ft_strcmp(cmd->operator, "<"))
	{
		((t_command *)lst->next->content)->skip_exec = true;
		cmd->file_input = true;
		cmd->redirect_path = ((t_command *)lst->next->content)->argv[0];
	}
}

void	fill_cmd_structs(t_list *lst)
{
	t_command	*cmd;

	while (lst)
	{
		cmd = lst->content;
		cmd->prog = cmd->argv[0];
		cmd->path = which(cmd->prog);
		if (!cmd->operator)
			;
		if (!ft_strcmp(cmd->operator, ";"))
			;
		else if (!ft_strcmp(cmd->operator, "|"))
		{
			cmd->need_pipe = true;
		}
		else
			parse_operators2(cmd, lst);
		lst = lst->next;
	}
}
