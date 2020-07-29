#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		err(1, "Atleast one argument expected.");
	}

	ssize_t i;
	ssize_t sctr = 0;
	ssize_t fctr = 0;

	for (i = 1; i < argc; i++)
	{
		int child = fork();

		if (child == 0)
		{
			if (execlp(argv[i], "child", NULL) == -1)
			{
				err(2, "Error executing command N%ld\n", i);
			}
			exit(0);
		}

		int status;
		wait(&status);
		if (WEXITSTATUS(status) == 0)
		{
			sctr++;
		}
		else
		{
			fctr++;
		}
	}

	printf("Success: %ld -- Fail: %ld\n", sctr, fctr);
	exit(0);

}
