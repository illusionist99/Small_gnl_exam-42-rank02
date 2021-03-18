#ifndef __GNL_H__
# define __GNL_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

# define BUFFER_SIZE 99

int					get_next_line(int fd, char **line);

#endif
