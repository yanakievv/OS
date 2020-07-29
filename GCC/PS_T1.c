#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <err.h>
#include <stdint.h>

int main()
{
	if (execlp("date", "date", (char*) NULL) == -1)
	{
		err(1, "Error executing command date.");
	}
}
