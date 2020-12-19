#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc , char*argv[])
{
	struct stat sb;
	int ret,ret2;
	FILE * fptr;
	// if(argc < 2){
	// 	printf(" enter file name \n");
	// 	exit(0);
	// }
	char oldpath[100];
	char c;
	printf("Enter old path\n");
	scanf("%s", oldpath);
	
	// printf(" file entered = %s",argv[1]);
	// ret = link("/home/student/Desktop/hello.txt","/home/student/Desktop/newname4");
	ret = link(oldpath,"/home/student/Desktop/newname4");
	fptr = fopen("/home/student/Desktop/newname4", "r"); 

	// print file using new filename
	printf(" content of file using new file name\n");
	c = fgetc(fptr);
	while(c!=EOF ){
		
		printf("%c\n",c );
		c = getc(fptr);
	}

	if(ret !=0){
		perror("link");
		// printf(" %m \n",errno );
		exit(0);
	}else{
		printf("soft link created new path : /home/student/Desktop/newname4 \n");
	}

	ret2 = unlink("/home/student/Desktop/newname4");

	if(ret2!=0){
		perror("unlink");
	}
	else{
		printf("path is unlinked \n");
	}

	return 0;
}
