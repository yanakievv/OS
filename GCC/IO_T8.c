#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <err.h>
#include <stdint.h>

int main()
{
	char* passwdpath = "/etc/passwd";
	char* newfilepath = "./passwd.txt";

	struct stat st;
	if (stat(passwdpath, &st) == -1)
	{
		err(1, "Error in determining passwd length.\n");
	}
	char* buf = malloc(st.st_size);

	int passwd = open(passwdpath, O_RDONLY);
	int newfile = open(newfilepath, O_WRONLY | O_CREAT | O_TRUNC, 00777);

	int i = 0;
	while (read(passwd, buf + i, 1) == 1)
	{
		if (buf[i] == ':')
		{
			buf[i] = '?';
		}
		++i;
	}

	if (write(newfile, buf, st.st_size) != st.st_size)
	{
		err(3, "Error while writing to file.\n");
	}

	close(passwd);
	close(newfile);
	free(buf);
	exit(0);
}
