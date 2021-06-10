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

void	check_write_redirect(t_command *cmd, t_list *cmds)
{
	if (!ft_strcmp(cmd->operator, ">") || !ft_strcmp(cmd->operator, ">>"))
	{
		if (cmds->next && (!ft_strcmp(
					((t_command *)cmds->next->content)->operator, ">")
				|| !ft_strcmp(((t_command *)cmds->next->content)->operator,
					">>")))
		{
			if (!ft_strcmp(((t_command *)cmds->next->content)->operator, ">"))
				print_buffer_in_file(cmd, false);
			else
				write_redirect(cmd->redirect_path, "", false, 0);
		}
		else
		{
			print_buffer_in_file(cmd, true);
			reset_pipe_output();
		}
	}
}

t_ptoken	*replace_env_var(t_ptoken *token)
{
	char	*doll;
	int		i;

	doll = ft_strchr(token->str, '$');
	i = doll - token->str;
	while (!token->squotes && doll)
	{
		doll = treat_doll(token, &i);
		doll = ft_strchr(doll + i, '$');
	}
	return (token);
}

char	**tab_add(char **argv, char *str)
{
	char	**res;
	char	**save;

	res = ft_calloc(sizeof(char *) * (ft_tab_len(argv) + 2));
	save = res;
	if (argv)
		while (*argv)
		{
			*res = ft_strdup(*argv);
			res++;
			argv++;
		}
	*res = ft_strdup(str);
	return (save);
}

char	**get_argv(t_ptoken *argv)
{
	char	**res;

	res = NULL;
	while (argv && argv->str)
	{
		// if (!argv->squotes)
			replace_env_var(argv);
		res = tab_add(res, argv->str);
		argv++;
	}
	return (res);
}