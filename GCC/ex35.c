#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <err.h>
#include <errno.h>

struct format
{
	uint16_t offset;
	uint8_t original;
	uint8_t new;
}__attribute__((packed));

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		err(1, "Improper usage. Proper is %s <.bin> <.bin> <.bin>", argv[0]);
	}

	struct stat st1;
	struct stat st2;

	if (stat(argv[1], &st1) == -1)
	{
		err(2, "Error statting file N1.");
	}

	if (stat(argv[2], &st2) == -1)
	{
		err(2, "Error statting file N2.");
	}

	if (st1.st_size != st2.st_size)
	{
		err(3, "Files must be of equal size.");
	}

	ssize_t fd1 = open(argv[1], O_RDONLY);
	ssize_t fd2 = open(argv[2], O_RDONLY);
	ssize_t patch = open(argv[3], O_CREAT | O_TRUNC | O_RDWR, 0777);
	uint8_t a;
	uint8_t b;

	struct format f;
	f.offset = 0;

	while (read(fd1, &a, sizeof(uint8_t)) == sizeof(uint8_t) && read(fd2, &b, sizeof(uint8_t)) == sizeof(uint8_t))
	{
		if (a != b)
		{
			f.original = a;
			f.new = b;

			if (write(patch, &f, sizeof(f)) != sizeof(f))
			{
				const int newerr = errno;
				close(fd1);
				close(fd2);
				close(patch);
				errno = newerr;
				err(4, "Error writing to patch file.");
			}
		}
		f.offset++;
	}

	close(fd1);
	close(fd2);
	close(patch);
	exit(0);



}
