#include "../../includes/minishell.h"

bool	join_tokens(t_ptoken *token)
{
	printf("dq %d sq %d sp %d str [%s]\n", (token + 1)->is_in_quotes,
		(token + 1)->is_in_squotes, (token + 1)->spaces, (token + 1)->str);
	if ((token + 1)->str
		&& ((token + 1)->is_in_quotes
			|| (token + 1)->is_in_squotes
			|| (token + 1)->spaces == 0))
		join_struct_wnext(token);
	else if ((token + 1)->str && ft_strlen((token + 1)->str) == 0)
		join_struct_wnext(token);
	else
		return (false);
	return (true);
}
