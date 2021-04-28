#include "../includes/minishell.h"

char	*get_word(char *line, char end, int i)
{
	int		j;
	int		len;
	char	*word;

	j = i;
	while (line[j] != end && line[j])
		j++;
	len = j - i;
	word = ft_calloc(sizeof(char) * (len + 1));
	j = 0;
	while (j < len)
		word[j++] = line[i++];
	return (word);
}

char	*get_word_sp(char *line, int i)
{
	int		j;
	int		len;
	char	*word;

	j = i;
	while (line[j] && ft_isalnum(line[j]))
		j++;
	len = j - i;
	word = ft_calloc(sizeof(char) * (len + 1));
	j = 0;
	while (j < len)
		word[j++] = line[i++];
	return (word);
}

size_t	get_word_len_sp(char *line, int i)
{
	int	j;

	j = i;
	while (line[j] && ft_isalnum(line[j]))
		j++;
	return (j - i);
}

char	*set_env_line(char *line, char *env_value, int i)
{
	char	*first_part;
	char	*final_part;

	first_part = get_word(line, '$', 0);
	final_part = ft_strjoin(first_part, env_value);
	final_part = ft_strjoin(final_part,
			line + i + 1 + get_word_len_sp(line, i + 1));
	return (final_part);
}

