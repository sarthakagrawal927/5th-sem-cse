#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	struct stat buf;
	if(argc<2){
		printf("insufficient entry\n");
		exit(1);
	}
	if(stat(argv[1],&buf)==-1){
		perror("fstat");
        exit(1);
	}

	printf("For the file %s struct stat is printed:\n\n",argv[1]);
	
	printf("-> ID of device is %ld\n",buf.st_dev);
	printf("-> inode no. %ld\n",buf.st_ino);
	printf("-> Permissions : %d\n",buf.st_mode);
	printf("-> No. of hard links : %ld\n",buf.st_nlink);
	printf("-> User id of owner : %d\n",buf.st_uid);
	printf("-> Group id of owner : %d\n",buf.st_gid);
	printf("-> Device id(special file) : %ld\n",buf.st_rdev);
	printf("-> Total size : %ld\n",buf.st_size);
	printf("-> Blocksize : %ld\n",buf.st_blksize);
	printf("-> No. of blocks : %ld\n",buf.st_blocks);
    printf("-> Last Access Time: %ld : %s\n",buf.st_atime,ctime(&(buf.st_atime)));
    printf("-> Last Modification Time: %ld : %s\n",buf.st_mtime,ctime(&(buf.st_mtime)));
    printf("-> Last Status Change Time: %ld : %s\n",buf.st_ctime,ctime(&(buf.st_ctime)));

	return 0;
}