#include "../../includes/minishell.h"

int	commant_not_found(char *cmd)
{
	ft_putstr_fd(2, "minishell: command not found: ");
	ft_putstr_fd(2, cmd);
	ft_putstr_fd(2, "\n");
	return (127);
}

int	syntax_error(void)
{
	ft_putstr_fd(2, "minishell: syntax error\n");
	return (126);
}

static void	exec(t_command cmd, char *envp[])
{
	display_array(envp);
	execve(cmd.path, cmd.argv, envp);
	close_subprocess(errno);
}

void	subprocess(t_command cmd, int *status)
{
	g_shell.child = fork();
	if (g_shell.child < 0)
		close_shell("fork error");
	else if (g_shell.child == 0)
	{
		signal(SIGQUIT, close_subprocess);
		signal(SIGINT, close_subprocess);
		exec(cmd, get_envp());
	}
	else
	{
		signals_listeners_to_child();
		wait(status);
		*status = (((*status) & 0xff00) >> 8);
	}
}

void	run_command(t_command *cmd, int *status)
{
	*status = 0;
	printf("NEW CMD\n");
	display_array(cmd->argv);
	printf("operator = %s\n", cmd->operator);
	wait_outputmanager(*cmd);
	if (!ft_strcmp(cmd->path, "builtin"))
		*status = exec_builtin(cmd->prog, cmd->argv);
	else
	{
		if (!cmd->path)
			*status = commant_not_found(cmd->prog);
		else
			subprocess(*cmd, status);
	// reset_pipe_output();
		if (cmd->need_pipe || cmd->need_redirect)
			close_pipe();
		g_shell.child = 0;
	}
}

int	run_line(char **argv)
{
	t_list		*cmds;
	t_command	*cmd;
	int			status;

	cmds = get_commands(argv);
	if (!cmds)
		return (syntax_error());
	reset_input_mode();
	while (cmds)
	{
		cmd = cmds->content;
		if (!cmd->skip_exec)
			run_command(cmd, &status);
		cmds = cmds->next;
	}
	add_signals_listeners();
	set_input_mode();
	return (status);
}
