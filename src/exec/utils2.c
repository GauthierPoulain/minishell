#include "../../includes/minishell.h"

t_buffer	*get_multiple_input(t_command cmd)
{
	t_buffer	*res;

	res = gc_malloc(sizeof(t_buffer));
	res->ptr = NULL;
	res->size = 0;
	if (g_shell.pipe_output.ptr)
	{
		res->ptr = ft_calloc(sizeof(char) * g_shell.pipe_output.size);
		ft_memcpy(res->ptr, g_shell.pipe_output.ptr, g_shell.pipe_output.size);
		res->size += g_shell.pipe_output.size;
	}
	if (cmd.file_input && is_a_file(cmd.redirect_path))
		get_input_part2(cmd, res);
	return (res);
}
