#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <err.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		err(1, "Expected arguments.\n");
	}

	int i;

	for (i = 1; i < argc; i++)
	{
		int fd = open(argv[i], O_RDONLY);
		if (fd == -1)
		{
			err(2, "Error while opening files.\n");
		}

		char buf[4096];
		ssize_t readsize;

		while ((readsize = read(fd, &buf, sizeof(buf))) > 0)
		{
			if (write(1, &buf, readsize) != readsize)
			{
				close(fd);
				err(3, "Error while writing to files.\n");
			}
		}
		close(fd);
		printf("\n");
	}

	exit(0);
}

