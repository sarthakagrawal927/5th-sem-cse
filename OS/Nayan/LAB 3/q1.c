#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	int status;
	pid = fork();
	if(pid<0){
		perror("fork failed\n");
		exit(1);
	}
	else if(pid==0){
			printf("Child running.......\nChild completed\n");
	}
	else{
           wait(&status);
           printf("Parent resumed\n");
           printf("Child returned : %d\n",status);
	}

	return 0;
}