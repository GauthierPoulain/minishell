#include "../../includes/minishell.h"

void	display_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		printf("(%s)\n", array[i]);
		i++;
	}
}

int	check_occurence(char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

size_t	get_word_len(char *word, int i)
{
	int	j;

	j = 0;
	while (word[i])
	{
		if (word[i] == ' ' || word[i] == '$'
			|| word[i] == '\\' || word[i] == '\"')
			return (j);
		i++;
		j++;
	}
	return (j);
}

void	join_if_needed(t_ptoken *array, int *i, int *size, t_list *lst)
{
	if (((t_token *)lst->content)->type == 10
		&& g_shell.trans)
	{
		join_no_space(array, i, size);
		array->is_escaped = true;
	}
	else if (((t_token *)lst->content)->type == 10)
		;
	else
		join_no_space(array, i, size);
}
