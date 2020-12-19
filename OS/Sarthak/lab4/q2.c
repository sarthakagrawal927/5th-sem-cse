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
	printf("ID pf device containing file : %ld\n", sb.st_dev);
	printf("Inode Number : %ld\n", sb.st_ino);
	printf("Permissions : %d\n", sb.st_mode);
	printf("Number of Hard Links : %ld\n", sb.st_nlink);
	printf("User ID of owner : %d\n", sb.st_uid);
	printf("Group ID of owner : %d\n", sb.st_gid);
	printf("Device ID : %ld\n", sb.st_rdev);
	printf("Total Size : %ld\n", sb.st_size);
	printf("Block Size : %ldbytes\n", sb.st_blksize);
	printf("Number of Blocks allocated : %ld\n", sb.st_blocks);
	printf("Last Access Time : %ld\n", sb.st_atime);
	printf("Last Modification Time : %ld\n", sb.st_mtime);
	printf("Last Status Change Time : %ld\n", sb.st_ctime);

	
	return 0;
}