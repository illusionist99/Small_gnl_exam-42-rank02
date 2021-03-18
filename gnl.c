
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define BUFFER_SIZE 99

int         ft_strlen(char *s)
{
    int i;

    i = 0;
    if (s)
        while (s[i] != '\0')
            i++;
    return (i);
}

char		*ft_join_n(char *s1, char *s2, int n)
{
	int	i;
	int	s1_len;
	char	*appended;

	i = 0;
	s1_len = ft_strlen(s1);
	if (!(appended = (char *)malloc(sizeof(char) * (s1_len + n + 1))))
		return (NULL);
	while (i < s1_len)
	{
		appended[i] = s1[i];
		i++;
	}
	if (s1)
		free(s1);
	while (i - s1_len < n)
	{
		appended[i] = s2[i - s1_len];
		i++;
	}
	appended[i] = '\0';
	return (appended);
}

int	get_next_line(int fd, char **line)
{
	int		i;
	static char	*tmp;
	char		*buff;
	char		*tmp_free;
	int		rd;

	*line = ft_join_n(NULL, NULL, 0);
	if (tmp)
	{
		i = 0;
		while (tmp[i] != '\0' && tmp[i] != '\n')
			i++;
		*line = ft_join_n(*line, tmp, i);
		if (tmp[i] == '\n')
		{
			tmp_free = ft_join_n(NULL, tmp + i + 1, ft_strlen(tmp + i + 1));
			free(tmp);
			tmp = ft_join_n(NULL, tmp_free, ft_strlen(tmp_free));
			free(tmp_free);	
			return (1);
		}
		free(tmp);
	}
	if (!(buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((rd = read(fd, buff, BUFFER_SIZE)))
	{
		if (rd < 0)
			return (-1);
		i = 0;
		buff[rd] = '\0';
		while (buff[i] != '\0' && buff[i] != '\n')
			i++;
		*line = ft_join_n(*line, buff, i);
		if (buff[i] == '\n')
		{
			tmp = ft_join_n(NULL, buff + i + 1, ft_strlen(buff + i + 1));
			free(buff);
			return (1);
		}
	}
	free(buff);
	return (0);
}

int     main(int ac, char **av)
{
    char    *s;
    int     fd;

	if (ac == 2)
	{
		fd = open(av[ac - 1],  O_RDONLY);
		s = NULL;
		
		while (get_next_line(fd, &s) == 1)
		{
			printf("%s\n", s);
			free(s);
		}
		// no newline in  the last line of file 
		printf("%s", s);
		free(s);
	}
	else
		printf("Usage ./a.out file\n");
    return (0);
}
