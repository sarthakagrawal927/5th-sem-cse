#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char const *argv[])
{
    int pfd[2];
    pid_t cpid;
    char buf;
 
    //Creating a pipe
    if(pipe(pfd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
 
    cpid = fork();
    if(cpid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
 
    if(cpid == 0){
        //Take a no as input and send it to the parent
 
        close(pfd[0]);
        int x;
        printf("Enter a no: ");
        scanf("%d", &x);
 
        //writing to a pipe
        write(pfd[1], &x, sizeof(int));
        close(pfd[1]);    //Reader sees this as EOF and stops reading
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pfd[1]);
        int y;
 
        //Reading from a pipe
        read(pfd[0], &y, sizeof(int));
        close(pfd[0]);
        printf("\nGot the no: %d, from the child!", y);
        wait(NULL);
    }
    return 0;
}