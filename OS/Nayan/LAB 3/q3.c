#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t pid,c_id,p_id;
	int status;
	pid = fork();
	if(pid<0){
		perror("fork failed\n");
		exit(1);
	}
	else if(pid==0){
		    c_id=getpid();
			p_id=getppid();
			printf("Child process with pid %d\n",c_id);
			printf("PID of parent : %d\n",p_id);
	}
	else{
           wait(NULL);
            c_id=getpid();
			p_id=getppid();
            printf("Parent process with pid %d\n",c_id);
			printf("PID of parent : %d\n",p_id);
			printf("PID of child : %d\n",pid);
		}

	return 0;
}