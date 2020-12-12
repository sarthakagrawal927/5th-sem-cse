#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	struct stat buf;
	if(argc<2){
		printf("insufficient entry\n");
		exit(1);
	}
	if(stat(argv[1],&buf)==-1){
		printf("error creating stat\n");
		exit(1);
	}
	printf("inode no. of %s is %ld\n",argv[1],buf.st_ino);

	return 0;
}