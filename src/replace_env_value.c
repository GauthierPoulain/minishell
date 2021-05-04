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

char	*get_word_dollar(char *line, int i)
{
	int		j;
	int		len;
	char	*word;

	j = i;
	while (line[j] != '$' && line[j])
		j++;
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
	if (j - i == 0)
		return (1);
	return (j - i);
}

char	*set_env_line(char *line, char *env_value, int i)
{
	char	*first_part;
	char	*final_part;

	if (line[i + 1] == '\\')
		first_part = get_word_dollar(line, 0);
	else
		first_part = get_word(line, '$', 0);
	final_part = ft_strjoin(first_part, env_value);
	final_part = ft_strjoin(final_part,
			line + i + 1 + get_word_len_sp(line, i + 1));
	return (final_part);
}

char	*replace_env_line(char **line)
{
	int		i;
	char	*env_value;
	char	*new_line;

	i = 0;
	new_line = *line;
	while (new_line[i])
	{
		if (new_line[i] == '$')
		{
			if (new_line[i + 1] == '?')
				env_value = ft_itoa(g_shell.last_return);
			else
				env_value = get_env(get_word_sp(new_line, i + 1));
			new_line = set_env_line(new_line, env_value, i);
			i = 0;
		}
		i++;
	}
	*line = new_line;
	return (*line);
}
