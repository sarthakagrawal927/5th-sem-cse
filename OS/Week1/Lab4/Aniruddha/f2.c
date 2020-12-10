#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

	printf("\n dev number = %ld\n",sb.st_dev);
	printf("\n inode number = %ld\n",sb.st_ino);
	printf("\n mode  = %d\n",sb.st_mode);
	printf("\n nlink  = %ld\n",sb.st_nlink);
	printf("\n uid number = %d\n",sb.st_uid);
	printf("\n gid number = %d\n",sb.st_gid);
	printf("\n device id = %ld\n",sb.st_rdev);
	printf("\n file size = %ld\n",sb.st_size);
	printf("\n block size = %ld\n",sb.st_blksize);
	printf("\n number of 512B blocks = %ld\n",sb.st_blksize);
	printf("\n time last accessed = %s\n",ctime(&sb.st_atim));
	printf("\n Last modified time: %s\n", ctime(&sb.st_mtim));
	printf("\n status change time: %s\n", ctime(&sb.st_ctim));
	return 0;
}
