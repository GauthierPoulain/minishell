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
	}
	close(fd);
}
