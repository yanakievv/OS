#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		err(1, "Invalid number of arguments.");
	}

	int fd1 = open(argv[1], O_RDWR, O_TRUNC);
	int fd2 = open(argv[2], O_RDWR, O_TRUNC);
	if (fd1 == -1 || fd2 == -1)
	{
		close(fd1);
		close(fd2);
		err(1, "Error opening files.");
	}

	struct stat st1;
	struct stat st2;
	if (stat(argv[1], &st1) == -1 || stat(argv[2], &st2) == -1)
	{
		close(fd1);
		close(fd2);
		err(2, "Error getting length of files.");
	}

	char* buf1 = malloc(st1.st_size);
	char* buf2 = malloc(st2.st_size);

	if (read(fd1, buf1, st1.st_size) != st1.st_size)
	{
		close(fd1);
		close(fd2);
		free(buf1);
		free(buf2);
		err(3, "Error while reading files.");
	}
	if (read(fd2, buf2, st2.st_size) != st2.st_size)
	{
		close(fd1);
		close(fd2);
		free(buf1);
		free(buf2);
		err(3, "Error while reading files.");
	}

	lseek(fd1, 0, SEEK_SET);
	lseek(fd2, 0, SEEK_SET);

	if (write(fd1, buf2, st2.st_size) != st2.st_size)
	{
		close(fd1);
		close(fd2);
		free(buf1);
		free(buf2);
		err(4, "Error while writing to files.");
	}
	if (write(fd2, buf1, st1.st_size) != st1.st_size)
	{
		close(fd1);
		close(fd2);
		free(buf1);
		free(buf2);
		err(4, "Error while writing to files.");
	}

	close(fd1);
	close(fd2);
	free(buf1);
	free(buf2);
	exit(0);

	
}
