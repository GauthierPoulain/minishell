#include "../includes/minishell.h"

void	final_word(char *line, t_lexer *lexer, t_token *token)
{
	if (ft_strlen(line))
	{
		printf("Second\n");
		if (line[i - 1])
		{
			token->id = id++;
			get_token_info(token, line, j, i);
			ft_lstadd_back(&g_shell.tokens, ft_lstnew(token));
		}
	}
}