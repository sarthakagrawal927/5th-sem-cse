#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
int main(int argc, char const *argv[])
{
	char line[100],ch,x[2];
	int i=0,count=0;
	if(argc!=3)
	{
		printf("\nInsufficient Arguments\n");
		exit(1);
	}
	int fd1,fd2;
	if((fd1=open(argv[1],O_RDONLY))==-1)
	{
		printf("\nError! File not found\n");
		exit(1);
	}
	if((fd2=open(argv[2],O_RDONLY))==-1)
	{
		printf("\nError! File not found\n");
		exit(1);
	}
	while(read(fd1,&ch,1)==1)
		{
			
				line[i]=ch;
				i++;
				line[i]='\0';
			if(ch=='\n')
			{	
				count++;
				printf("Line %d: %s",count,line);
				if(count%20==0)
				{
					printf("Press enter for more");
					fgetc(stdin);
				}
				i=0;
			}
		}
	count=0;
	i=0;
	printf("Press enter for next file");
					fgetc(stdin);
	while(read(fd2,&ch,1)==1)
		{
			
				line[i]=ch;
				i++;
				line[i]='\0';
			if(ch=='\n')
			{	
				count++;
				printf("Line %d: %s",count,line);
				if(count%20==0)
				{
					printf("Press enter for more");
					fgetc(stdin);
				}
				i=0;
			}
		}

	return 0;
}
