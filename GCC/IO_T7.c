#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		err(1, "Arguments expected.\n");
	}

	char* dirpath = argv[argc-1];

	int dir_fd = open(dirpath, O_DIRECTORY);

	if (dir_fd == -1)
	{
		err(2, "Error with opening directory.\n");
	}

	int wr = access(dirpath, W_OK);

	if (wr == -1)
	{
		err(2, "Directory not writable.\n");
	}

	int length = (int)strlen(dirpath);

	if (dirpath[length-1] != '/')
	{
		strcat(dirpath,"/");
		length++;
	}

	printf("%s", dirpath);

	int i = 1;

	for(; i < argc - 1; i++)
	{
		char* temp = malloc(255);
		int j = 0;
		for (; dirpath[j] != '\0'; j++)
		{
			temp[j] = dirpath[j];
		}
		strcat(temp, argv[i]);
		int fdfrom = open(argv[i], O_RDONLY);
		int fdto = open(temp, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
		char buf[4096];
		ssize_t read_size;
		while ((read_size = read(fdfrom, &buf, sizeof(buf))) > 0)
		{
			if (write(fdto, &buf, read_size) != read_size)
			{
				close(dir_fd);
				close(fdfrom);
				close(fdto);
				err(3, "Error while writing to files.\n");
			}
		}
		free(temp);	
	}

	exit(0);
	
}
