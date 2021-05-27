#include "../../includes/minishell.h"

void	set_output(t_command cmd)
{
	g_shell.saved_stdout = dup(1);
	g_shell.saved_stderr = dup(2);
	if (pipe(g_shell.pipes.to_father) != 0 || pipe(g_shell.pipes.to_son) != 0)
		close_shell("pipe error");
	g_shell.outputmngr = fork();
	if (g_shell.outputmngr < 0)
		close_shell("fork error");
	else if (g_shell.outputmngr == 0)
		manage_output(cmd);
	if (cmd.need_redirect)
	{
		if (cmd.redirect_stdout)
			dup2(g_shell.pipes.to_son[1], 1);
		if (cmd.redirect_stderr)
			dup2(g_shell.pipes.to_son[1], 2);
	}
	else if (cmd.need_pipe)
	{
	}
}

void	reset_output(void)
{
	dup2(g_shell.saved_stdout, 1);
	dup2(g_shell.saved_stderr, 2);
	close(g_shell.saved_stdout);
	close(g_shell.saved_stderr);
}

void	manage_output(t_command cmd)
{
	char	*buff;
	char	*new_buff;
	int		len;
	char	*end;
	bool	read_pipe;
	char	*tmp;

	read_pipe = true;
	if (cmd.need_redirect)
		write_redirect(cmd, "", true, 0);
	buff = ft_calloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	new_buff = ft_calloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	end = ft_calloc_char(sizeof(char) * (GNL_BUFFER_SIZE + 1), -1);
	ft_putchar_fd(g_shell.pipes.to_father[1], EOF);

	len = read(g_shell.pipes.to_son[0], buff, GNL_BUFFER_SIZE);
	while (read_pipe)
	{

		len = read(g_shell.pipes.to_son[0], new_buff, GNL_BUFFER_SIZE);

		if (!ft_memcmp(new_buff, end, GNL_BUFFER_SIZE))
		{
			read_pipe = false;
			tmp = ft_memchr(buff, -1, GNL_BUFFER_SIZE);
			while (tmp)
			{
				*tmp = 0;
				tmp = ft_memchr(buff, -1, GNL_BUFFER_SIZE);
			}
			print_debug_termcap(buff);
		}

		process_pipe(cmd, buff, len);
		ft_memcpy(buff, new_buff, GNL_BUFFER_SIZE);



	}
	close_subprocess(0);
}
