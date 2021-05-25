#include "../../includes/minishell.h"

void	write_redirect(t_command cmd, char *buffer, bool erease, int len)
{
	int		fd;

	if (erease)
		fd = open(cmd.redirect_path, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0775);
	else
		fd = open(cmd.redirect_path, O_WRONLY | O_APPEND | O_CREAT, 0775);
	write(fd, buffer, len);
	close(fd);
}

void	process_pipe(t_command cmd, char *buffer, int len)
{
	cut_eof(buffer);
	// write(1, buffer, len);
	// ft_putcolor(buffer, _BLUE);
	if (cmd.need_redirect)
		write_redirect(cmd, buffer, false, len);
	ft_bzero(buffer, GNL_BUFFER_SIZE + 1);
}
