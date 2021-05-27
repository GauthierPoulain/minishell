#include "../includes/minishell.h"

void	print_debug_termcap(char *c)
{
	printf("new key\n");
	printf("key = %d, char = %c\n", c[0], c[0]);
	printf("key = %d, char = %c\n", c[1], c[1]);
	printf("key = %d, char = %c\n", c[2], c[2]);
	printf("key = %d, char = %c\n", c[3], c[3]);
	printf("key = %d, char = %c\n", c[4], c[4]);
	printf("key = %d, char = %c\n", c[5], c[5]);
	printf("key = %d, char = %c\n", c[6], c[6]);
	printf("key = %d, char = %c\n", c[7], c[7]);
	printf("key = %d, char = %c\n", c[8], c[8]);
	printf("key = %d, char = %c\n", c[9], c[9]);
	printf("done\n");
}
