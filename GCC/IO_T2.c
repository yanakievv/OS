#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		err(1, "Invalid number of arguments\n");
	}

	int fd = open(argv[1], O_RDONLY);

	struct stat st;

	if (stat(argv[1], &st) == -1)
	{
		err(3, "error");
	}

	char temp;
	int ctr = 0;

	while (ctr < 10)
	{
		if (read(fd, &temp, 1) != 1)
		{
			break;
		}

		write(1, &temp, 1);

		if (temp == '\n')
		{
			ctr++;
		}
	}

	close(fd);
	exit(0);


}
