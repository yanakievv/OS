#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <err.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char* argv[])
{
	const char* dest = argv[2];
	const char* arg = argv[1];
	if (argc != 3)
	{
		err(1, "Expecting 2 arguments.");
	}

	if (strcmp(arg, "--min") && strcmp(arg, "--max") && strcmp(arg, "--print"))
	{
		err(1, "First argument must be from the list: --min, --max, --print");
	}

	int fd = open(dest, O_RDONLY);

	struct stat st;

	if (stat(dest, &st) == -1)
	{
		err(2, "Error with determining file length.");
	}


	uint16_t* buf = malloc(st.st_size);
	int i = 0;
	uint16_t temp;
	int j = 0;
	ssize_t readsize;

	while ((readsize = read(fd, &temp, sizeof(uint16_t))) > 0)
	{
		if (readsize != sizeof(uint16_t))
		{
			free(buf);
			close(fd);
			err(3, "Error while reading from file.");
		}
		buf[j++] = temp;
	}

	uint16_t comp = buf[0];


	if (!strcmp(arg, "--print"))
	{
		for (; i < j; i++)
		{
			printf("%x\n", buf[i]);
		}
		
		free(buf);
		close(fd);
		exit(0);
	}
	else if (!strcmp(arg, "--min"))
	{
		for (; i < j; i++)
		{
			if (buf[i] < comp)
			{
				comp = buf[i];
			}
		}
	}
	else 
	{
		for (; i < st.st_size; i++)
		{
			if (buf[i] > comp)
			{
				comp = buf[i];
			}
		}
	}

	printf("%x\n", comp);
	//printf("%ld : %d\n", st.st_size, j);
	free(buf);
	close(fd);
	exit(0);

}
