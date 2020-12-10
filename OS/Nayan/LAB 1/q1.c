#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#define SZ 500

int main(int argc, char const *argv[])
{
	char c,line[SZ];
	int i=0;
	int fd = open(argv[2],O_RDONLY);
    while(read(fd,&c,1)==1){
    	if(c=='\n'){
           if(strstr(line,argv[1])!=NULL){
           	line[i++]='\n';
           	line[i]='\0';
           	write(1,line,i);
      
        }
           i=0;

    	}
    	else{
    	 line[i++]=c;
    	 line[i]='\0';
    	}
    }
    close(fd);
	return 0;
}