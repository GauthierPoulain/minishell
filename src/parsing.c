#include "../includes/minishell.h"

void	test(char **words, int i, t_list *lst)
{
	int		vars;
	char	*env_value;

	vars = check_occurence(((t_token *)lst->content)->str, '$');
	if (vars > 1)
		words[i] = replace_env_line(&((t_token *)lst->content)->str);
	else
	{
		if (((t_token *)lst->content)->str[1] == '\\')
		{
			words[i] = ft_strndup(((t_token *)lst->content)->str, 1);
			words[i] = ft_strjoin(words[i], ((t_token *)lst->content)->str + 2);
		}
		if (((t_token *)lst->content)->str[1] == '?')
			env_value = ft_itoa(g_shell.last_return);
		else
			env_value = get_env(((t_token *)lst->content)->str + 1);
		words[i] = ft_strdup(env_value);
	}
}

void	if_forest(char **words, int i, t_list *lst)
{
	if (((t_token *)lst->content)->id == 0)
		words[i] = replace_env_line(&((t_token *)lst->content)->str);
	if (((t_token *)lst->content)->type == 2)
		test(words, i, lst);
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
