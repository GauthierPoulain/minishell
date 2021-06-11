#include "../../includes/minishell.h"

static void	parse_operators2(t_command *cmd, t_list *lst)
{
	if (!ft_strcmp(cmd->operator, ">"))
	{
		((t_command *)lst->next->content)->skip_exec = true;
		cmd->need_redirect = true;
		cmd->redirect_path = ((t_command *)lst->next->content)->token->str;
	}
	else if (!ft_strcmp(cmd->operator, ">>"))
	{
		((t_command *)lst->next->content)->skip_exec = true;
		cmd->need_redirect = true;
		cmd->redirect_append = true;
		cmd->redirect_path = ((t_command *)lst->next->content)->token->str;
	}
	else if (!ft_strcmp(cmd->operator, "<"))
	{
		((t_command *)lst->next->content)->skip_exec = true;
		cmd->file_input = true;
		cmd->redirect_path = ((t_command *)lst->next->content)->token->str;
	}
}

bool	fill_cmd_structs(t_command *cmd, t_list *lst)
{
	if (cmd->operator && !ft_strcmp(cmd->operator, "noop"))
		return (false);
	if (!cmd->operator)
		;
	else if (!ft_strcmp(cmd->operator, ";"))
		;
	else if (!ft_strcmp(cmd->operator, "|"))
		cmd->need_pipe = true;
	else
		parse_operators2(cmd, lst);
	return (true);
}
