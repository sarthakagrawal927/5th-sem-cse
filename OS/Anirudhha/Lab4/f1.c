#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc , char*argv[])
{
	struct stat sb;
	int ret;
	if(argc < 2){
		printf(" enter file name \n");
		exit(0);
	}

	printf(" file entered = %s",argv[1]);
	ret = stat(argv[1],&sb);

	if(ret){
		perror("stat");
		exit(0);
	}

	printf("\n inode number = %ld",sb.st_ino);

	return 0;
}
