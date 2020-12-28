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
    int pipe_fd, res, bytes_read, buffer , count;

    if(access(FIFO, F_OK) == -1){
        res = mkfifo(FIFO,0777);
    }

    pipe_fd = open(FIFO,O_WRONLY);
    printf("Process %d result %d\n", getpid(), pipe_fd);

    if(pipe_fd !=-1){
        do{
            res = read(pipe_fd, &buffer, sizeof(int));
            printf("\nInteger read is %d",buffer);
            bytes_read += res;
            count++;
        }
        while(bytes_read < 4*sizeof(int));
    }
    printf("Process %d finished ", getpid());
    return 0;
}
