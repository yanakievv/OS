#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <err.h>
#include <stdint.h>

struct pair
{
	uint32_t from;
	uint32_t to;
};

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		err(1, "Expecting 2 arguments.");
	}

	int fd1 = -1, fd2 = -1, fd3 = -1;

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd3 = open(argv[3], O_CREAT | O_TRUNC | O_RDWR, 0777);

	struct pair p;
	ssize_t readsize;
	uint32_t buf;
	ssize_t ctr = 0;

	while ((readsize = read(fd1, &p, sizeof(p))) > 0)
	{
		lseek(fd2, SEEK_SET, (p.from - 1)*sizeof(uint32_t));
		ssize_t readsize2;
		while ((readsize2 = read(fd2, &buf, sizeof(buf))) > 0)
		{
			if (write(fd3, &buf, sizeof(buf)) == -1)
				{
					err(2, "Error writing to file.");
				}
			ctr++;
			if (ctr == p.to)
			{
				break;
			}
		}

	}

}
