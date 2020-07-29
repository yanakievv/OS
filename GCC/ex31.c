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
	if (argc != 2)
	{
		err(1, "Expected one argument.");
	}
	
	struct stat st;

	if (stat(argv[1], &st) == -1)
	{
		err(2, "Error while statting file.");
	}
	if(!(st.st_mode & S_IRUSR) || !(st.st_mode & S_IWUSR))
	{
		err(3, "File not readable or writable.");
	}

	uint64_t counting[256] = { 0 };

	ssize_t fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		err(4, "Error opening binary file.");
	}

	ssize_t readsize;
	uint8_t b;

	while ((readsize = read(fd, &b, sizeof(b))) == sizeof(b))
	{
		counting[b]++;
	}

	lseek(fd, SEEK_SET, 0);

	uint16_t i = 0;

	for (; i < 256; i++)
	{
		b = i;

		while(counting[i]--)
		{
			if(write(fd, &b, sizeof(b)) != sizeof(b))
			{
				err(5, "Error writing to file.");
			}
		}
	}

	close(fd);
	exit(0);
}	
