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
		    printf("Child process\nBeginning execution of q1.c\n");
		    printf("****************\n");
			execlp("../part1/q1","q1",NULL);
			
	}
	else{
           wait(NULL);
		   printf("****************\n");
           printf("Child completed\n");

	}

	return 0;
}