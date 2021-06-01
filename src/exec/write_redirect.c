#include "../../includes/minishell.h"

void	init_write_recursivly(t_list *lst)
{
	t_command	*act;

	while (lst
		&& (!ft_strcmp(((t_command *)lst->content)->operator, ">")
			|| !ft_strcmp(((t_command *)lst->content)->operator, ">>")))
	{
		act = lst->content;
		if (!act->redirect_append)
			write_redirect(act->redirect_path, "", true, 0);
		lst = lst->next;
	}
}

void	write_recursivly(char *buffer, int len, t_list *lst)
{
	t_command	*act;

	while (lst
		&& (!ft_strcmp(((t_command *)lst->content)->operator, ">")
			|| !ft_strcmp(((t_command *)lst->content)->operator, ">>")))
	{
		act = lst->content;
		write_redirect(act->redirect_path, buffer, false, len);
		lst = lst->next;
	}
}
