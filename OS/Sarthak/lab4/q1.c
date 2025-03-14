#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	struct stat sb;
	int ret;
	if (argc < 2)
	{
		fprintf(stderr, "file name not mentioned%s\n",argv[0] );
		return 1;
	}
	ret = stat(argv[1],&sb);
	if(ret){
		perror("stat");
		return 1;
	}
	printf("Inode Number : %ld", sb.st_ino);
	
	return 0;
}