#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	execlp("sleep", "sleep", "100", NULL);
}
