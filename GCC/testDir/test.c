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
	int fd = open(argv[1], O_RDONLY);
	struct stat st;
	stat(argv[1], &st);
	uint32_t* p = malloc(st.st_size);
	read(fd, p, st.st_size);
	qsort(p, st.st_size/sizeof(uint32_t), sizeof(uint32_t), cmp);
	int print = open("binsort", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	write(print, p, st.st_size);
}
