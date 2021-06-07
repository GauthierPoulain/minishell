#include "../includes/minishell.h"

bool	check_int_overflow(char *str)
{
	char	*tmp;
	bool	res;

	tmp = ft_itoa(ft_atoi(str));
	if (*str == '+')
		str++;
	if (*str == '-')
	{
		str++;
		while (*str == '0' && ft_strlen(str) > 1)
			str++;
		if (*str != '0')
		{
			str--;
			*str = '-';
		}
	}
	else
		while (*str == '0' && ft_strlen(str) > 1)
			str++;
	res = ft_strcmp(str, tmp);
	return (res != 0);
}

int	builtin_exit(char **argv)
{
	int		ret;

	ret = 0;
	if (isatty(STDIN_FILENO))
		ft_putstr("exit\n");
	if (argv && argv[1] && check_int_overflow(argv[1]))
		ret = 255;
	else if (argv && argv[1] && ((argv[1][1] && !ft_isdigit(argv[1][1]))
			|| (!argv[1][1] && !ft_isdigit(argv[1][0]))))
		ret = 255;
	else if (argv && argv[1] && argv[2])
		ret = 1;
	else if (argv && argv[1])
		ret = ft_atoi(argv[1]);
	// close_pipe();
	reset_input_mode();
	gc_clean();
	exit(ret);
}
