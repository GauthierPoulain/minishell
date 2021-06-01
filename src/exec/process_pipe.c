#include "../../includes/minishell.h"

void	write_redirect(char *path, char *buffer, bool erease, int len)
{
	int		fd;

	if (erease)
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC,
				0644);
	else
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	write(fd, buffer, len);
	close(fd);
}

void	*ft_memjoin(void *s1, size_t l1, void *s2, size_t l2)
{
	char	*res;

	res = ft_calloc(sizeof(char) * (l1 + l2));
	if (s1)
		ft_memcpy(res, s1, l1);
	gc_free(s1);
	ft_memcpy(res + l1, s2, l2);
	return (res);
}

static void	write_recursivly(char *buffer, int len, t_list *lst)
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

void	process_pipe(t_command cmd, char *buffer, int len, t_list *lst)
{
	if (cmd.need_redirect)
		write_recursivly(buffer, len, lst);
	else if (cmd.need_pipe)
	{
		g_shell.pipe_output.ptr = ft_memjoin(g_shell.pipe_output.ptr,
				g_shell.pipe_output.size, buffer, len);
		g_shell.pipe_output.size += len;
	}
	ft_bzero(buffer, GNL_BUFFER_SIZE + 1);
}
