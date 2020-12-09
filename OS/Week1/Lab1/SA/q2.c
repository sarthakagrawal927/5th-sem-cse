#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#define SZ 100000

int main(int argc, char const *argv[])
{
	char c;
	if(argc < 2){
		printf("Insufficient Arguments\n");
		exit(0);
	}
    int line=1;        

    for(int i = 1; i < argc; i++){

        printf("File Name %s\n",argv[i]);
        int in = open(argv[i],O_RDONLY);
        if(in == -1){
            printf("File Not found\n");
        }

        char buffer[SZ];
        int buffer_length;
    
        read(in, buffer, sizeof(buffer));
        buffer_length=strlen(buffer);
        printf("Line 1 : ");

        for (int i = 0; i < buffer_length; i++) 
        {

            printf("%c",buffer[i]);
            if (buffer[i] == '\n') 
            {
                line++;
                 printf("Line %d : ", line);
                  if(line % 20 == 0) getchar();
            }

            buffer[i] = 0; 
        }
        printf("\n");
    }
	return 0;
}