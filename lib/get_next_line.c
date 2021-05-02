#include "../includes/minishell.h"

static char	*fetch_line(char *str)
{
	int		i;
	char	*res;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != 10)
		i++;
	res = gc_malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != 10)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

static char	*fetch_save(char *save)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != 10)
		i++;
	if (!save[i])
	{
		gc_free(save);
		return (NULL);
	}
	res = gc_malloc(sizeof(char) * ((ft_strlen(save) - i) + 1));
	i++;
	while (save[i])
		res[j++] = save[i++];
	res[j] = 0;
	gc_free(save);
	return (res);
}

static bool	customchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	if (c == 0)
		return (1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*save[10240];
	int			readvalue;

	readvalue = 1;
	if (fd < 0 || !line || GNL_BUFFER_SIZE < 1)
		return (-1);
	buffer = gc_malloc(sizeof(char) * (GNL_BUFFER_SIZE + 1));
	while (readvalue != 0 && !customchr(save[fd], '\n'))
	{
		readvalue = read(fd, buffer, GNL_BUFFER_SIZE);
		if (readvalue == -1)
		{
			gc_free(buffer);
			return (-1);
		}
		buffer[readvalue] = 0;
		save[fd] = ft_strjoinf1(save[fd], buffer);
	}
	gc_free(buffer);
	*line = fetch_line(save[fd]);
	save[fd] = fetch_save(save[fd]);
	if (readvalue == 0)
		return (0);
	return (1);
}
