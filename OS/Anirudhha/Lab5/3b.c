#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
#define TEN_MEG (1024*1024*10)

int main()
{
	while(1){
	int pipe_fd;
	int res=0;
	int open_mode=O_RDONLY;
	int bytes_read=0;
	char buffer1[BUFFER_SIZE+1];
	memset(buffer1,'\0',sizeof(buffer1));
	
	pipe_fd=open(FIFO_NAME,open_mode);
	
	if(pipe_fd!=-1)
	{
		do
		{
			res=read(pipe_fd,buffer1,BUFFER_SIZE);
			bytes_read+=res;
		}while(res==0);
		(void)close(pipe_fd);
		printf("Process 1 says: %s\n", buffer1);
		if(strcmp(buffer1,"exit")==0)
			break;
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	
	res=0;
	open_mode=O_WRONLY;
	int bytes_sent=0;
	char buffer2[BUFFER_SIZE+1];
	
	pipe_fd=open(FIFO_NAME,open_mode);
	
	if(pipe_fd!=-1)
	{
			
		printf("Enter text: ");
		scanf("%s",buffer2);
		res=write(pipe_fd,buffer2,BUFFER_SIZE);
		if(res==-1)
		{
			fprintf(stderr, "Write error on pipe\n");
			exit(EXIT_FAILURE);
		}
		bytes_sent+=res;
			
		
		(void)close(pipe_fd);
		if(strcmp(buffer2,"exit")==0)
			break;
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	}
}