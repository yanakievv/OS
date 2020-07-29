#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <err.h>

int main()
{
	int fd = open("./testDir/PS_T9_addon.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);

	int child = fork();

	if (child == 0)
	{
		if (write(fd, "bar", 3) == -1)
		{
			close(fd);
			err(1, "Error writing to file.");
		}
	}
	else
	{
		if (write(fd, "foo", 3) == -1)
		{
			close(fd);
			err(2, "Error writing to file.");
		}
	}
	close(fd);
	exit(0);
}
