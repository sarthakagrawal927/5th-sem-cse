#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<fcntl.h>
#include<string.h>
 
#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
 
int main(int argc, char const *argv[])
{
    mkfifo(FIFO_NAME, 0666);
    //This program will first read and then write
    char buffer[1024]; 
    int res, pipe_fd;
 
    if(access(FIFO_NAME, F_OK) == -1){
        printf("pipe does not exist\n");
        res = mkfifo(FIFO_NAME, 0777);
        if(res != 0){
            fprintf(stderr, "could not create fifo %s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }
 
    //step 1: Read from the pipe
    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, O_RDONLY);
 
    memset(buffer, '\0', sizeof(buffer));
    read(pipe_fd, buffer, 1024);
    close(pipe_fd);
 
    printf("Output: Process %d reads -> %s\n", getpid(), buffer);
 
    //step 2: write to the pipe
    printf("Process %d opening FIFO O_WRONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, O_WRONLY);
 
    printf("Input: ");
    memset(buffer, '\0', sizeof(buffer));
    fgets(buffer, 1024, stdin);
 
    write(pipe_fd, buffer, strlen(buffer)+1);
    close(pipe_fd);
 
    return 0;
}