#include "../../includes/minishell.h"

t_command	init_cmd_struct(char **argv)
{
	t_command	cmd;

	cmd.argv = argv;
	cmd.prog = argv[0];
	cmd.path = which(cmd.prog);
	cmd.need_pipe = false;
	cmd.need_redirect = false;
	cmd.redirect_stdout = true;
	cmd.redirect_stderr = true;
	cmd.redirect_path = ft_strdup("salut");
	return (cmd);
}
