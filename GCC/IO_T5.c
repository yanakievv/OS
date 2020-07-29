#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		err(1, "Invalid number of arguments.\n");
	}

	int fd1 = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_CREAT | O_WRONLY, S_IRWXU);

	if (fd1 == -1 || fd2 == -1)
	{
		close(fd1);
		close(fd2);
		err(2, "Error while opening files.\n");
	}

	char buf[4096];
	ssize_t read_size;

	while ((read_size = read(fd1, &buf, sizeof(buf))) > 0)
	{
		if (write(fd2, &buf, read_size) != read_size)
		{
			close(fd1);
			close(fd2);
			err(3, "Error while writing to files.\n");
		}
	}

	close(fd1);
	close(fd2);

	exit(0);

}
