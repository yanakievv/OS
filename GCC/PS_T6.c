#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		err(1, "Expecting 1 argument.");
	}

	int pid = fork();
	
	if (pid == 0)
	{
		execlp(argv[1], "child", NULL);
	}
	else
	{
		wait(&pid);
		if (WIFEXITED(pid))
		{
			printf("%s\n", argv[1]);
		}
	}


	exit(0);
}
