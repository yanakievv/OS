#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <err.h>
#include <stdint.h>

int main()
{
	//execlp("ls", "ls", "-alh", (char*) NULL);
	char* args[] = {"kurec", "100", NULL};
	execvp("sleep", args);
	
}

