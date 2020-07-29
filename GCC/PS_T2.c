#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	execlp("ls", "ls", "./testDir", NULL);
}
