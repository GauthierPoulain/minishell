#include "../includes/minishell.h"

static bool	custom_read(int fd, char *buffer, int *readvalue)
{
	*readvalue = read(fd, buffer, 1);
	// printf("c = %c, int = %d\n", *buffer, *buffer);
	// write(1, buffer, 1);
	return (*readvalue != 0);
}

int	ft_gnl(int fd, char **line)
{
	char	buffer;
	int		ret;
	int		readvalue;

	ret = 0;
	if (!line)
		return (-1);
	*line = gc_malloc(sizeof(char));
	if (!*line)
		return (-1);
	*line[0] = 0;
	while (custom_read(fd, &buffer, &readvalue) && buffer != '\n')
		*line = ft_strjoinc(*line, buffer);
	if (!*line)
		*line = ft_strjoinc(*line, 0);
	if (readvalue > 0)
		ret = 1;
	return (ret);
}
