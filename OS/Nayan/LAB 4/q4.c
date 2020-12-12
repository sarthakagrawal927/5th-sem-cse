#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int ret;

	if(argc<2){
		printf("insufficient entry\n");
		exit(1);
	}
    printf("before link\n");
    system("ls -il");
    ret = symlink(argv[1],"./softlink");
    if(ret){
    	perror("symlink");
    	exit(1);
    }
    printf("after link\n");
    system("ls -il");

    ret=unlink("./softlink");

    if(ret){
    	perror("unlink");
    	exit(1);
    }

    printf("unlinked new path\n");
    system("ls -il");  

	return 0;
}