#include "../../includes/minishell.h"

static void	quotes_job(t_ptoken *token)
{
	if ((token + 1)->str && (token + 1)->spaces > 0
		&& ((!(token)->is_in_quotes && (token + 1)->is_in_quotes)
			|| (!(token)->is_in_squotes && (token + 1)->is_in_squotes)))
	{
		(token + 1)->str = ft_strjoin(ft_calloc_char(((token + 1)->spaces) + 1,
					' '), (token + 1)->str);
		(token + 1)->spaces = -1;
	}
	if ((token + 1)->spaces_after > 0 && ((token + 1)->is_in_quotes
			|| (token + 1)->is_in_squotes))
	{
		(token + 1)->str = ft_strjoin((token + 1)->str,
				ft_calloc_char((token + 1)->spaces_after + 1, ' '));
		(token + 1)->spaces_after = -1;
	}
}

bool	join_tokens(t_ptoken *token)
{
	quotes_job(token);
	if (!(token)->skip_join && (token + 1)->str && (((token)->is_in_quotes
				&& (token + 1)->is_in_quotes) || ((token)->is_in_squotes
				&& (token + 1)->is_in_squotes) || ((token + 1)->spaces == 0)))
		join_struct_wnext(token);
	else if (!(token)->skip_join && (token + 1)->str && ft_strlen((token + 1)->str) == 0
		&& !(token + 1)->escapes && ((token + 1)->is_in_quotes
			|| !(token)->is_in_squotes) && (token)->spaces <= 0)
		join_struct_wnext(token);
	else
		return (false);
	return (true);
}

void	donccacestmavie(t_ptoken *argv, int *i)
{
	if ((argv + *i + 1)->str && (argv + *i + 2)->str
		&& (argv + *i + 3)->str && !(argv + *i)->is_in_quotes
		&& (argv + *i + 1)->is_in_quotes
		&& !(argv + *i + 3)->is_in_quotes)
		(argv + *i + 1)->skip_join = true;
	if ((argv + *i + 1)->str && (argv + *i + 2)->str
		&& (argv + *i + 3)->str && !(argv + *i)->is_in_squotes
		&& (argv + *i + 1)->is_in_squotes
		&& !(argv + *i + 3)->is_in_squotes)
		(argv + *i + 1)->skip_join = true;
}
