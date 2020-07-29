#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		err(1, "Two arguments expected.");
	}

	char* buf = "foobar";



	pid_t child = fork();

	if (child == -1)
	{

		err(2, "Error creating a new process.");
	}
	if (child == 0)
	{
		int fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0777);

		if (write(fd, buf, strlen(buf)) == -1)
		{
			close(fd);
			err(3, "Error writing to file.");
		}
		close(fd);
		exit(0);
	}
	
	int fd = open(argv[1], O_RDONLY);
	int status;
	wait(&status);
	
	uint16_t check[2];
	ssize_t readsize;

	if (WIFEXITED(status))
	{
		
		while ((readsize = read(fd, &check, sizeof(char) * 2)) > 0)
		{	
			write(1, &check, sizeof(char) * 2);
			write(1, " ", 1);
		}

	}
	else
	{	
		
		close(fd);
		err(5, "Child did not exit properly.");
	}
	

	exit(0);


}
