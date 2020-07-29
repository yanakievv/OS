#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <err.h>
#include <stdint.h>

int cmp(const void *a, const void* b){
	if ( *((uint32_t*)a) > *((uint32_t*)b) )
		return 1;
	else if ( *((uint32_t*)a) < *((uint32_t*)b) )
		return -1;
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		err(1, "Expected one argument.");
	}

	char *bin = argv[1], *sorted = argv[2];

	struct stat st;

	if (stat(bin, &st) == -1)
	{
		err(2, "Error statting file.");
	}

	if (st.st_size % sizeof(uint32_t) != 0)
	{
		err(3, "File is corrupted.");
	}

	uint32_t nums = st.st_size / sizeof(uint32_t);
	uint32_t half = nums / 2;

	uint32_t* p = malloc(half*sizeof(uint32_t));

	int fd1 = open(argv[1], O_RDONLY);
	int t1 = open("temp1", O_CREAT | O_TRUNC | O_RDWR, 0777);
	read(fd1, p, half*sizeof(uint32_t));

	qsort(p, half, sizeof(uint32_t), cmp);
	write(t1, p, half*sizeof(uint32_t));
	free(p);

	uint32_t rhalf = nums - half;
	uint32_t* rp = malloc(sizeof(uint32_t)*rhalf);

	int t2 = open("temp2", O_CREAT | O_TRUNC | O_RDWR, 0777);
	read(fd1, rp, rhalf*sizeof(uint32_t));

	qsort(rp, rhalf, sizeof(uint32_t), cmp);
	write(t2, rp, rhalf*sizeof(uint32_t));

	free(rp);
	close(fd1);

	lseek(t1, SEEK_SET, 0);
	lseek(t2, SEEK_SET, 0);

	int fd2 = open(sorted, O_CREAT | O_TRUNC | O_RDWR, 0777);

	uint32_t c1 = 0;
	uint32_t c2 = 0;
	ssize_t rd1;
	ssize_t rd2;
	uint32_t a, b;
	while (((rd1 = read(t1, &a, sizeof(uint32_t))) == sizeof(uint32_t)) && ((rd2 = read(t2, &b, sizeof(uint32_t))) == sizeof(uint32_t)))
	{
		if (a <= b)
		{
			write(fd2, &a, sizeof(uint32_t));
			lseek(t2, SEEK_CUR, (-1)*sizeof(uint32_t));
			c1++;
		}
		else
		{
			write(fd2, &b, sizeof(uint32_t));
			lseek(t1, SEEK_CUR, (-1)*sizeof(uint32_t));
			c2++;
		}
	}

	if (c1 < c2)
	{
		while ((rd1 = read(t1, &a, sizeof(uint32_t))) > 0)
		{
			if (write(fd2, &a, sizeof(uint32_t)) == -1)
			{
				err(3, "Error writing to file");
			}
		}
	}
	else if (c2 < c1)
	{
		while ((rd2 = read(t2, &b, sizeof(uint32_t))) > 0)
		{
			if (write(fd2, &b, sizeof(uint32_t)) == -1)
			{
				err(3, "error writing to file");
			}
		}
	}






}
