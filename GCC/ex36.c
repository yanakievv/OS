#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>


void READ(ssize_t fd, const char* arg, int  numerate)
{
	char c;
	ssize_t readsize;
	uint8_t newline = 1;

	while ((readsize = read(fd, &c, 1)) == 1)
	{
		if (numerate)
		{
			if (newline)
			{
				setbuf(stdout, NULL);
				fprintf(stdout, "%d ", numerate);
				write(1, &c, 1);
				newline--;
				numerate++;
			}
			else write(1, &c, 1);
			if (c == '\n')
			{
				newline++;
			}
		}
		else write(1, &c, 1);
	}

}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		err(1, "Incorrect usage, use: %s [OPTION] [FILE]...", argv[0]);
	}

	int numerate = 0;

	if (strcmp(argv[1], "-n") == 0)
	{
		numerate = 1;
	}

	uint16_t i = 1;

	for (; i < argc; i++)
	{
		if (strcmp(argv[i], "-") == 0)
		{
			READ(0, "STDIN", numerate);
		}
		else
		{
			ssize_t fd = open(argv[i], O_RDONLY);
			READ(fd, argv[i], numerate);
		}
	}

}
