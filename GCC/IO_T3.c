#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		err(1, "Invalid number of arguments");
	}

	int fd = open(argv[1], O_RDONLY);

	if (fd == -1)
	{
		err(2, "Error while opening file.");
	}

	int ctr=0;
	int linectr=0;
	int wordctr=0;

	char c;

	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			linectr++;
			wordctr++;
		}
		if (c == ' ')
		{
			wordctr++;
		}

		ctr++;
	}

	printf("%d %d %d\n", ctr, wordctr, linectr);

	close(fd);
	exit(0);
}
