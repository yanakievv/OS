#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		err(1, "Arguments must be 3: cfile file1 file2\n");
	}
	
	int fd_cpyfrom = open(argv[1], O_RDONLY);
	int fd_cpyto = open(argv[2], O_RDWR, O_TRUNC, O_CREAT, 00777);

	if (fd_cpyfrom == -1 || fd_cpyto == -1)
	{
		err(2, "error");
	}

	struct stat st;
	if (stat(argv[1], &st) == -1)
	{
		err(3, "error");
	}

	void *buff = malloc(st.st_size);

	if (read(fd_cpyfrom, &buff, st.st_size) != st.st_size)
	{
		err(4, "error");
	}

	if (write(fd_cpyto, &buff, st.st_size) != st.st_size)
	{
		err(5, "error");
	}

	close(fd_cpyfrom);
	close(fd_cpyto);
	free(buff);
	exit(0);
}
