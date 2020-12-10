#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){

	printf(" I am the previous program \n");
	int status;
	pid_t pid;
	pid = fork();
	if(pid == -1){
		printf(" child not created \n");
		exit(0);
	}

	else if(pid==0){
		printf(" i am in child \n");
		exit(0);
	}

	else{
		wait(&status);
		printf(" i am in parent\n");
		printf(" child returned = %d\n", status);
	}

	return 0;
}