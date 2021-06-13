#include "../../includes/minishell.h"

bool	join_tokens(t_ptoken *token)
{
	if ((token + 1)->str
		&& ((!(token)->is_in_quotes && (token + 1)->is_in_quotes)
			|| (!(token)->is_in_squotes && (token + 1)->is_in_squotes)
			|| (token + 1)->spaces == 0))
		join_struct_wnext(token);
	else if ((token + 1)->str && ft_strlen((token + 1)->str) == 0
			&& !(token + 1)->escapes && ((token + 1)->is_in_quotes
			|| !(token)->is_in_squotes) && (token)->spaces <= 0)
		join_struct_wnext(token);
	else
		return (false);
	return (true);
}
