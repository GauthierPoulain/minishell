#include "../../includes/minishell.h"

void	get_input_part2(t_command cmd, t_buffer *res)
{
	int			fd;
	int			len;
	char		*buffer;

	buffer = ft_calloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	fd = open(cmd.redirect_path, O_RDONLY);
	len = 1;
	while (len > 0)
	{
		len = read(fd, buffer, GNL_BUFFER_SIZE);
		res->ptr = ft_memjoin(res->ptr, res->size, buffer, len);
		res->size += len;
		ft_bzero(buffer, GNL_BUFFER_SIZE + 1);
	}
}

t_buffer	*get_multiple_input(t_command cmd)
{
	t_buffer	*res;

	res = gc_malloc(sizeof(t_buffer));
	res->ptr = NULL;
	res->size = 0;
	if (cmd.file_input && is_a_file(cmd.redirect_path))
		get_input_part2(cmd, res);
	else if (g_shell.pipe_output.ptr)
	{
		res->ptr = ft_calloc(sizeof(char) * g_shell.pipe_output.size);
		ft_memcpy(res->ptr, g_shell.pipe_output.ptr, g_shell.pipe_output.size);
		res->size += g_shell.pipe_output.size;
	}
	return (res);
}

int	is_operator(char *c)
{
	if (*c == '>' && *(c + 1) == '>')
		return (2);
	else if (ft_ischarset(*c, ";><|"))
		return (1);
	else
		return (0);
}

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

int	child_supervisor(t_buffer *data, bool read_pipe, int pipes[2])
{
	int			status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (read_pipe)
		print_buffer_in_fd(*data, pipes[1]);
	reset_pipe_output();
	waitpid(g_shell.child, &status, 0);
	close(pipes[0]);
	close(pipes[1]);
	if ((((signed char)(((status) & 0x7f) + 1) >> 1) > 0))
	{
		status = ((status) & 0x7f);
		if (status == 2)
			return (130);
		else if (status == 3)
			return (131);
		else
			return (status);
	}
	else
		return (((status) & 0xff00) >> 8);
}
