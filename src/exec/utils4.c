#include "../../includes/minishell.h"

bool	join_tokens(t_ptoken *token)
{
	if ((token + 1)->str && ((token + 1)->is_in_quotes
			|| (token + 1)->is_in_squotes
			|| (token + 1)->spaces == 0))
		join_struct_wnext(token);
	else
		return (false);
	return (true);
}
