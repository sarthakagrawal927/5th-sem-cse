#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();

    if(pid < 0){
        fprintf(stderr,"Fork Failed");
        exit(0);
    }
    else if(pid == 0){
        execlp("/bin/ls","ls",NULL);
    }
    else{
        wait(NULL);
        printf("%d\n",getpid());
        printf("Child Completed");
        execlp("./q5","./q5"  ,NULL);

        exit(0);
    }
    return 0;
}
