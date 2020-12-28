#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<fcntl.h>
#include<string.h>

#define FIFO "./my_fifo"

int main(int argc, char const *argv[])
{
    int pipe_fd, res, bytes_sent, buffer , count;

    if(access(FIFO, F_OK) == -1){
        res = mkfifo(FIFO,0777);
        if(res != 0){
            fprintf(stderr, "could not create fifo %s\n", FIFO);
            exit(EXIT_FAILURE);
        }
    }

    pipe_fd = open(FIFO,O_WRONLY);
    printf("Process %d result %d\n", getpid(), pipe_fd);

    if(pipe_fd !=-1){
        do{
               printf("\nEnter an integer: ");
            scanf("%d", &buffer);
            res = write(pipe_fd, &buffer, sizeof(int));
            if(res == -1){
            bytes_sent += res;
            count++;
        }
        }while(bytes_sent < 4*sizeof(int));
          (void)close(pipe_fd);
    }
    else perror("error");
    printf("Process %d finished ", getpid());
    return 0;
}
