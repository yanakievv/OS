#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>

struct format
{
	uint16_t offset;
	uint8_t length;
	uint8_t filler;
}__attribute__((packed));


int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		err(1, "Improper usage, proper is: %s <.dat> <.idx> <.dat> <.idx>", argv[0]);
	}

	struct stat st;
	if (stat(argv[2], &st) == -1)
	{
		err(2, "Error statting %s.", argv[2]);
	}

	if (st.st_size % sizeof(uint32_t) != 0)
	{
		err(3, "Corrupted file %s.", argv[2]);
	}

	ssize_t fd1 = open(argv[1], O_RDONLY);
	ssize_t fd2 = open(argv[2], O_RDONLY);
	ssize_t fd3 = open(argv[3], O_CREAT | O_TRUNC | O_RDWR, 0777);
	ssize_t fd4 = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0777);

	if (fd1 == -1 || fd2 == -1 || fd3 == -1 || fd4 == -1)
	{
		const int newerr = errno;
		close(fd1);
		close(fd2);
		close(fd1);
		close(fd2);
		errno = newerr;
		err(3, "Error opening files.");
	}

	struct format f;
	f.filler = 0;
	struct format fp;
	fp.offset = 0;
	fp.filler = 0;

	while (read(fd2, &f, sizeof(f)) > 0)
	{
		uint8_t* temp = malloc(f.length);
		lseek(fd1, 0, SEEK_SET);
		read(fd1, temp, f.length);
		printf("%s\n", temp);
		if (temp[0] > 'A' && temp[0] < 'Z')
		{
			write(fd3, temp, f.length);
			fp.length = f.length;
			write(fd4, &fp, sizeof(fp));
			fp.offset = fp.offset + fp.length;
		}
		free(temp);
	}

	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	exit(0);
}
	
	
