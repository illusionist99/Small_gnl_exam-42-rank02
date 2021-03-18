#include "gnl.h"

int     main(int ac, char **av)
{
    char    *s;
    int     fd;

	if (ac == 2)
	{
		fd = open(av[ac - 1],  O_RDONLY);
		s = NULL;
        // ! get_next_line prototype only if you want to check tests folder :)
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
