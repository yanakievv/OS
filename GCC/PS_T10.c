#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		err(1, "Expected 2 arguments.");
	}

	int child = fork();

	if (child == 0)
	{
		if (execlp(argv[1], "child", NULL) == -1)
		{
			err(2, "Error executing first command.");
		}
		exit(0);
	}

	int status;
	wait(&status);

	if (WEXITSTATUS(status) == 0)
	{
		if (execlp(argv[2], "parent", NULL) == -1)
		{
			err(3, "Error executing second command.");
		}

	}
	else
	{
		err(42, "First command did not exit correctly.");
	}
}
