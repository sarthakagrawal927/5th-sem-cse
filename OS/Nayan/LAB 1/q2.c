#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#define SZ 500

int main(int argc, char const *argv[])
{
	char c;
	int i,j=0;
  for(i=1;i<argc;i++){
	  int fd = open(argv[i],O_RDONLY);
    //j=0;
    while(read(fd,&c,1)==1){
    	if(c=='\n'){
           j++;
           //printf("\n");

           if(j!=0&&j%20==0){
                 fgetc(stdin);
                
           }
        

    	}
    	
      write(1,&c,1);
    
    }
    printf("*********************************\n");
    close(fd);
  }
	return 0;
}