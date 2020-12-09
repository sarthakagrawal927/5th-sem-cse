#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#define SZ 100000

int main(int argc, char const *argv[])
{
	char c;
	if(argc < 2){
		printf("Insufficient Arguments\n");
		exit(0);
	}

    int in = open(argv[1],O_RDONLY);
    if(in == -1){
        printf("File Not found\n");
    }
    int out = open(argv[2], O_WRONLY);
    if(out == -1){
        printf("File Not found\n");
    }

    while(read(in,&c,1) == 1) write(out,&c,1);

	return 0;
}