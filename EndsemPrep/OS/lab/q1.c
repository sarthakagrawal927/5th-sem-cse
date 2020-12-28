#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int pf[2];
    pid_t cpid;
    char buf;

    if(pipe(pf) == -1){
        exit(EXIT_FAILURE);
    }

    cpid = fork();

    if(cpid ==-1) {
        exit(EXIT_FAILURE);
    }

    if(cpid == 0){
        close(pf[0]);
        int x;
        printf("Enter");
        scanf("%d",&x);
        write(pf[1] , &x, sizeof(int));
        close(pf[1]);
    }
    else{
        close(pf[1]);
        int y;
        read(pf[0], &y,sizeof(int));
        close(pf[0]);
        printf("From c %d",y);
        wait(NULL);
    }
    return 0;
}
