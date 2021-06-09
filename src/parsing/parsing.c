#include "../../includes/minishell.h"

void	chose_parsing(char **word, t_list *lst)
{
	if (((t_token *)lst->content)->type == 4)
		*word = parse_d_quotes(((t_token *)lst->content)->str);
	else if (((t_token *)lst->content)->type == 6)
		*word = parse_s_quotes(((t_token *)lst->content)->str);
	else
	{
		if (DEBUG)
			printf("ALED OUI\n");
		*word = parse_tokens(((t_token *)lst->content)->str);
	}
}

void	join_no_space(char **words, int *i, int *size)
{
	char	*tmp;

	printf("JOINED MA BOI\n");
	tmp = ft_strdup(words[*i]);
	words[*i] = NULL;
	gc_free(words[*i]);
	words[*i - 1] = ft_strjoin(words[*i - 1], tmp);
	*i -= 1;
	*size -= 1;
}

static void	things(t_list *lst, char **words, int i)
{
	g_shell.curr_token = (t_token *)lst->content;
	if (lst->next)
		g_shell.next_token_str = ((t_token *)lst->next->content)->str;
	chose_parsing(&words[i], lst);
	g_shell.curr_token = NULL;
	g_shell.next_token_str = NULL;
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
	while (i < size && lst && g_shell.error == false)
	{
		things(lst, words, i);
		if (g_shell.error == true)
			return (NULL);
		if (!((t_token *)lst->content)->sp
			&& ((t_token *)lst->content)->id >= 1
			&& check_type_at(i - 1) != 10)
		{
			if (((t_token *)lst->content)->type == 10
				&& g_shell.trans)
			join_no_space(words, &i, &size);
			else if (((t_token *)lst->content)->type == 10)
				;
			else
				join_no_space(words, &i, &size);
		}
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
	g_shell.error = false;
	g_shell.is_in_quotes = false;
	g_shell.is_in_s_quotes = false;
	array = array_from_list();
	if (P_ARRAY && array)
		display_array(array);
	return (array);
}
