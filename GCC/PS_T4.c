#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int n = 9999999;
	int pid = fork();	

	if (pid > 0)
	{
		int j;
		for (j = 0; j < n; j++)
		{
			printf("father\n");
		}
	}
	else
	{
		int j;
		for (j = 0; j < n; j++)
		{
			printf("child\n");
		}
	}
	exit(0);
}
