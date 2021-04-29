#include "../includes/minishell.h"

void	display_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("(%s)\n", array[i]);
		i++;
	}
}

char	**array_from_list()
{
	int		size;
	int		i;
	t_list	*lst;
	char	**words;
	char	*env_value;

	i = 0;
	size = ft_lstsize(g_shell.tokens);
	words = gc_malloc(sizeof(char *) * (size + 1));
	lst = g_shell.tokens;
	while (i < size)
	{
		if (((t_token *)lst->content)->type == 2)
		{
			env_value = get_env(((t_token *)lst->content)->str + 1);
			words[i] = ft_strdup(env_value);
		}
		else
			words[i] = ft_strdup(((t_token *)lst->content)->str);
		lst = lst->next;
		i++;
	}
	words[i] = NULL;
	return (words);
}

char	**parse_line(char *line)
{
	char	**array;

	get_lexer(line);
	array = array_from_list();
	display_array(array);
	return (array);
	// TODO : don't forget to free the array later
}