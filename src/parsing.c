#include "../includes/minishell.h"

/*
//	I don't even know why I did that, it's ugly, it works. For now
*/

void	if_forest(char **words, int i, t_list *lst)
{
	if (((t_token *)lst->content)->id == 0)
	{
		if (((t_token *)lst->content)->type == 3)
			words[i] = ft_strdup(((t_token *)lst->content)->str + 1);
		else
			words[i] = parse_tokens(((t_token *)lst->content)->str);
	}
	else if (((t_token *)lst->content)->type == 2)
		words[i] = parse_tokens(((t_token *)lst->content)->str);
	else
	{
		if (check_occurence(((t_token *)lst->content)->str, '$')
			|| check_occurence(((t_token *)lst->content)->str, '\\'))
			words[i] = parse_tokens(((t_token *)lst->content)->str);
		else
			words[i] = ft_strdup(((t_token *)lst->content)->str);
	}
}

void	chose_parsing(char **word, t_list *lst)
{
	if (((t_token *)lst->content)->type == 4)
		*word = parse_d_quotes(((t_token *)lst->content)->str);
	else
		*word = parse_tokens(((t_token *)lst->content)->str);
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
	while (i < size && g_shell.error == false)
	{
		chose_parsing(&words[i], lst);
		if (words[i] == NULL)
			break ;
		if (g_shell.error == false)
			lst = lst->next;
		else
			return (NULL);
		i++;
	}
	words[i] = NULL;
	return (words);
}

char	**parse_line(char *line)
{
	char	**array;

	get_lexer(line);
	g_shell.error = false;
	array = array_from_list();
	if (DEBUG && array)
		display_array(array);
	return (array);
}
