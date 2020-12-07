#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
int main(int argc, char const *argv[])
{
	char line[100],ch;
	int i=0,count=0;
	if(argc!=3)
	{
		printf("\nInsufficient Arguments\n");
		exit(1);
	}
	int fd;
	if((fd=open(argv[2],O_RDONLY))==-1)
	{
		printf("\nError! File not found\n");
		exit(1);
	}
	while(read(fd,&ch,1)==1)
		{
				line[i]=ch;
				i++;
				line[i]='\0';
			if(ch=='\n')
			{	
				count++;
				if(strstr(line,argv[1]))
					{	
						printf("Line %d: %s",count,line);
					}
				i=0;
			}
		}
	return 0;
}
