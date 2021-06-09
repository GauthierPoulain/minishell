#include "../includes/minishell.h"

int	get_this_char(char **c, char **retour)
{
	char	*res;

	if (!*c)
		*retour = NULL;
	else
	{
		res = ft_calloc(sizeof(char) * 2);
		if ((0x80 & **c) == 0)
		{
			res = ft_strjoinc(res, **c);
			*c += 1;
			*retour = res;
		}
		else
		{
			while ((0x80 & **c) != 0)
			{
				res = ft_strjoinc(res, **c);
				*c += 1;
			}
			*retour = res;
		}
	}
	return (1);
}

char	*get_str_rterm(char **str)
{
	char	*res;

	res = ft_strdup("");
	if (!str)
		return (NULL);
	while (*str)
	{
		res = ft_strjoinf1(res, *str);
		str++;
	}
	return (res);
}

void	put_in_term(char **line, char ***str, t_reader *reader)
{
	if (line)
	{
		while (*line)
		{
			print_char(str, *line, reader, false);
			line++;
		}
	}
}
