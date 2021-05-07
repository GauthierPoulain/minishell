#include "../includes/minishell.h"

/*
//	seems to have some issues with the replace_env_line for token id 0
*/

void	if_forest(char **words, int i, t_list *lst)
{
	if (((t_token *)lst->content)->id == 0)
		words[i] = parse_env_var(((t_token *)lst->content)->str);
	else if (((t_token *)lst->content)->type == 2)
		words[i] = parse_env_var(((t_token *)lst->content)->str);
	else if (((t_token *)lst->content)->type == 3)
		words[i] = ft_strdup(((t_token *)lst->content)->str + 1);
	else
		words[i] = ft_strdup(((t_token *)lst->content)->str);
}

char	**array_from_list(void)
{
	int		size;
	int		i;
	t_list	*lst;
	char	**words;

	i = 0;
	size = ft_lstsize(g_shell.tokens);
	words = gc_malloc(sizeof(char *) * (size + 1));
	lst = g_shell.tokens;
	while (i < size)
	{
		if_forest(words, i, lst);
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
}
