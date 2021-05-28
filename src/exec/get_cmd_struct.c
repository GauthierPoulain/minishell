#include "../../includes/minishell.h"

t_command	init_cmd_struct(char **argv)
{
	t_command	cmd;

	cmd.argv = argv;
	cmd.prog = argv[0];
	cmd.path = which(cmd.prog);
	cmd.need_pipe = false;
	cmd.need_redirect = false;
	cmd.redirect_append = false;
	cmd.redirect_path = ft_strdup("salut");
	cmd.listen_stdout = true;
	cmd.listen_stderr = true;
	return (cmd);
}
