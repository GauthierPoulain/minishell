#include "../includes/minishell.h"

void	chose_parsing(char **word, t_list *lst)
{
	if (((t_token *)lst->content)->type == 4)
		*word = parse_d_quotes(((t_token *)lst->content)->str);
	else
		*word = parse_tokens(((t_token *)lst->content)->str);
}

void	join_no_space(char **words, int *i, int *size)
{
	char	*tmp;

	tmp = ft_strdup(words[*i]);
	words[*i] = NULL;
	gc_free(words[*i]);
	words[*i - 1] = ft_strjoin(words[*i - 1], tmp);
	*i -= 1;
	*size -= 1;
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
		if (!((t_token *)lst->content)->sp
			&& ((t_token *)lst->content)->id >= 1)
			join_no_space(words, &i, &size);
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
	if (P_ARRAY && array)
		display_array(array);
	return (array);
}
