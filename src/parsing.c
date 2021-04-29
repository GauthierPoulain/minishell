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

	i = 0;
	size = ft_lstsize(g_shell.tokens);
	words = gc_malloc(sizeof(char *) * (size + 1));
	lst = g_shell.tokens;
	while (i < size)
	{
		words[i] = ft_strdup(((t_token *)lst->content)->str);
		lst = lst->next;
		i++;
	}
	words[i] = NULL;
	return (words);
}

