#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){
	int status;
	pid_t pid;
	pid = fork();
	if(pid == -1){
		printf(" child not created \n");
		exit(0);
	}

	else if(pid==0){
		printf(" i am in child with PID : %d\n",getpid());
		printf(" parent PID : %d\n",getppid());
		exit(0);
	}

	else{
		wait(&status);
		printf(" i am in parent with PID : %d\n",getpid());
		printf(" the PID of my child is PID : %d\n",pid );
		printf(" child returned = %d\n", status);
	}

	return 0;
}