#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <err.h>
#include <errno.h>
#include <stdint.h>

int main()
{
	int pipefd[2];
	pipe(pipefd);

	if (fork() == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		execlp("cat", "cat", "/etc/passwd", NULL);
	}

	close(pipefd[1]);

	int pipefd2[2];
	pipe(pipefd2);

	if (fork() == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd2[0]);
		dup2(pipefd2[1], 1);
		execlp("cut", "cut", "-d", ":", "-f7", NULL);
	}
	
	close(pipefd2[1]);
	dup2(pipefd2[0], 0);
	execlp("sort", "sort", NULL);

	exit(0);
	
	
}
