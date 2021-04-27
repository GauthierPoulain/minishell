#include "../includes/minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	char	*rdest;

	rdest = dest;
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	return (rdest);
}
