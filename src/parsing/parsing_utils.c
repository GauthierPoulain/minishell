#include "../../includes/minishell.h"

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
