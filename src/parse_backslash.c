#include "../includes/minishell.h"

static size_t	bslash_f_count(char *word, int i)
{
	int	j;

	j = 0;
	while (word[i] == '\\')
	{
		i++;
		j++;
	}
	return (j);
}

static int	real_bslash(int nb)
{
	// if (nb % 2)
	// 	return (0);
	return (((nb / 2) + 1) / 2);
}

char	*bslash_first(char *word, int *i)
{
	(void)word;
	(void)i;
	return (NULL);
}

char	*treat_backslash(char *word, int *i, int *trans)
{
	char	*new;

	int	back;
	int	r_back;
	if (*i == 0)
	{
		back = bslash_f_count(word, *i);
		printf("b_slash count : %d\n", back);
		if (back % 2 && ft_strlen(word) == (size_t)back)
		{
			ft_putstr_fd(2, "Syntax error");
			return ("");
		}
		else
		{
			r_back = real_bslash(back);
			if (back % 4 == 2)
			{
				if (word[r_back + 1] == '$')
				{
					r_back -= 1;
					new = ft_calloc_char(r_back + 1, '\\');
					*i = r_back;
					return(new);
				}
			}
			printf("r_back = %d\n", r_back);
			new = ft_calloc_char(r_back + 1, '\\');
			new = ft_strjoin(new, word + back);
			*i += real_bslash(back);
			printf("back modul : %d\n", back % 4);
			printf("r back : %d\n", r_back);
			if (back % 4 == 1)
			{
				*trans = 0;
				printf("word during the changes [%s]\n", new);
			}
			return (new);
		}
		*i += back;
		return (ft_strdup(word + 1));
	}
	return (NULL);
}
