#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		err(1, "Expected 3 arguments.");
	}
	
	int status;
	pid_t child1 = fork();

	if (child1 == -1)
	{
		err(2, "Error with forking child1.");
	}

	if (child1 == 0)
	{
		if (execlp(argv[1], "child1", NULL) == -1)
		{
			err(3, "Error executing command N1.");
		}
	}

	if (wait(&status) == -1)
	{
		err(4, "Error waiting for chil1.");
	}

	printf("%d -- %d\n", child1, WEXITSTATUS(status));

	pid_t child2 = fork();

	if (child2 == -1)
	{
		err(2, "Error forking child2.");
	}
	if (child2 == 0)
	{
		if (execlp(argv[2], "child2", NULL) == -1)
		{
			err(3, "Error executing command N2.");
		}
	}

	if (wait(&status) == -1)
	{
		err(4, "Error waiting for child2.");
	}

	printf("%d -- %d\n", child2, WEXITSTATUS(status));

	pid_t child3 = fork();

	if (child3 == -1)
	{
		err(2, "Error forking child3.");
	}

	if (child3 == 0)
	{
		if (execlp(argv[3], "child3", NULL) == -1)
		{
			err(3, "Error executing command N3.");
		}
	}

	if (wait(&status) == -1)
	{
		err(4, "Error while waiting for child3.");
	}

	printf("%d -- %d\n", child3, WEXITSTATUS(status));

	exit(0);


}
