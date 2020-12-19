#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
int main(int argc, char const *argv[])
{
	char ch;
	int res;
	if(argc!=3)
	{
		printf("\nInsufficient Arguments\n");
		exit(1);
	}
	int in,out;
	if((in=open(argv[1],O_RDONLY))==-1)
	{
		printf("\nError! File not found\n");
		exit(1);
	}
	if((out=open(argv[2],O_WRONLY))==-1)
	{
		printf("\nError! File not found\n");
		exit(1);
	}
	while(read(in,&ch,1)==1)
		{
			res=write(out,&ch,1);				
		}
	if(res!=-1)
		printf("File copied successfully.\n");
	return 0;
}
