#include "../../includes/minishell.h"

bool	join_tokens(t_ptoken *token)
{
	printf("%s %d %d %d\n", (token)->str, (token)->spaces,
		(token)->is_in_quotes, (token)->is_in_squotes);
	if ((token + 1)->spaces > 0 && ((token + 1)->is_in_quotes
			|| (token + 1)->is_in_squotes))
	{
		printf("salut\n");
		(token + 1)->str = ft_strjoin(ft_calloc_char(((token + 1)->spaces) + 1,
					'_'), (token + 1)->str);
		(token + 1)->spaces = -1;
	}
	if ((token + 1)->str && (((token)->is_in_quotes
				&& (token + 1)->is_in_quotes) || ((token)->is_in_squotes
				&& (token + 1)->is_in_squotes) || ((token + 1)->spaces == 0)))
		join_struct_wnext(token);
	else if ((token + 1)->str && ft_strlen((token + 1)->str) == 0
		&& !(token + 1)->escapes && ((token + 1)->is_in_quotes
			|| !(token)->is_in_squotes) && (token)->spaces <= 0)
		join_struct_wnext(token);
	else
		return (false);
	return (true);
}
